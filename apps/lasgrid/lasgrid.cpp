#include "CLI11.hpp"

#include <spatiumgl/Bounds.hpp>
#include <spatiumgl/Vector.hpp>
#include <spatiumgl/io/LasReader.hpp>
#include <spatiumgl/io/LasWriter.hpp>

#include <unordered_map> // std::unordered_map

int
main(int argc, char* argv[])
{
  // Parse command-line arguments
  CLI::App app{ "Filter LAS/LAZ point cloud with voxel grid filter." };
  std::string fileIn;
  app.add_option("-i,--input", fileIn, "Input LAS/lAZ file")
    ->required()
    ->check(CLI::ExistingFile);
  std::string fileOut;
  app.add_option("-o,--output", fileOut, "Output LAS/lAZ file")
    ->required()
    ->check(CLI::NonexistentPath);
  double spacing;
  app.add_option("-s,--spacing", spacing, "Spacing, grid cell size")
    ->required();
  CLI11_PARSE(app, argc, argv)

  spgl::io::LasReader reader(fileIn);
  if (!reader.isReady()) {
    std::cerr << "Unable to open input file." << std::endl;
    return 1;
  }

  if (!reader.open()) {
    std::cerr << "Failed to open input file." << std::endl;
    return 1;
  }

  spgl::BoundingBox extent = reader.lasHeader().extent;

  // Create grid for points
  std::unordered_map<std::string, spgl::io::LasPoint> grid;

  // Iterate points in input file
  int progressPercentage = 0;
  long long onePercent = reader.lasHeader().number_of_point_records / 100;
  long long pointsProcessed = 0;

  while (reader.readLasPoint()) {
    const spgl::io::LasPoint& lasPoint = reader.lasPoint();

    // Compute cell index in grid
    const spgl::Vector3i gridIndex = (lasPoint.xyz / spacing).staticCast<int>();
    const std::string gridIndexKey = std::to_string(gridIndex[0]) + "|" +
                                     std::to_string(gridIndex[1]) + "|" +
                                     std::to_string(gridIndex[0]);

    // Get grid cell point (if existing)
    if (grid.find(gridIndexKey) == grid.end()) {
      // No point in grid cell -> insert first point
      grid[gridIndexKey] = lasPoint; // copy assignment
    } else {
      // Point already in grid cell -> replace if closer to cell center
      const spgl::io::LasPoint cellPoint = grid[gridIndexKey];

      // Compute distance to grid cell center
      const spgl::Vector3 cellCenter =
        (gridIndex.staticCast<double>() * spacing) +
        spgl::Vector3(0.5 * spacing);
      const double distanceGridPoint = cellCenter.distance(cellPoint.xyz);
      const double distanceNewPoint = cellCenter.distance(lasPoint.xyz);

      if (distanceNewPoint < distanceGridPoint) {
        // Replace point in grid cell
        grid[gridIndexKey] = lasPoint; // copy assignment
      }
    }

    // Update & print progress
    pointsProcessed++;
    if (onePercent > 0) {
      int curProgress = static_cast<int>(pointsProcessed / onePercent);

      if (curProgress > progressPercentage) {
        int diff = curProgress - progressPercentage;
        for (int i = 0; i < diff; i++) {
          std::cout << "." << std::flush;
        }

        progressPercentage = curProgress;
      }
    }
  }
  std::cout << std::endl;

  // Write grid points to file
  spgl::io::LasWriter writer(fileOut);
  if (!writer.isReady()) {
    std::cerr << "Unable to open output file." << std::endl;
    return 1;
  }
  if (!writer.open(reader.lasHeader())) {
    std::cerr << "Failed to open output file." << std::endl;
    return 1;
  }

  // Write grid points to file
  for (const auto& gridCell : grid) {
    writer.writeLasPoint(gridCell.second);
  }
  writer.close();

  reader.close();

  return 0;
}
