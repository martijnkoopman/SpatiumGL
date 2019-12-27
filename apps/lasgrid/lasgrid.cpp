#include "CLI11.hpp"

#include "lasreader.hpp" // LASlib
#include "laswriter.hpp" // LASlib

#include <unordered_map> // std::unordered_map
#include <cstring> // std::memcpy, std::memset

using Point = std::array<double, 3>;
using Extent = std::array<Point, 2>;

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

  // Open input file
  LASreadOpener lasReadOpener;
  lasReadOpener.set_file_name(fileIn.c_str());
  if (!lasReadOpener.active()) {
    std::cerr << "Unable to open file." << std::endl;
    return 1;
  }
  std::unique_ptr<LASreader> lasReader(lasReadOpener.open());
  if (lasReader == nullptr) {
    std::cerr << "Failed to open file." << std::endl;
    return 1;
  }

  // Read extent of input file
  Extent extent{ Point{ lasReader->header.min_x,
                        lasReader->header.min_y,
                        lasReader->header.min_z },
                 Point{ lasReader->header.max_x,
                        lasReader->header.max_y,
                        lasReader->header.max_z } };

  // Create grid for points
  std::unordered_map<std::string, LASpoint> grid;

  // Iterate points in input file
  int progressPercentage = 0;
  long long onePercent = lasReader->header.number_of_point_records / 100;
  long long pointsProcessed = 0;

  Point position;
  while (lasReader->read_point()) {
    position[0] = lasReader->point.get_x();
    position[1] = lasReader->point.get_y();
    position[2] = lasReader->point.get_z();

    // Compute cell index in grid
    std::array<int, 3> gridIndex{
      static_cast<int>((position[0] - extent[0][0]) / spacing),
      static_cast<int>((position[1] - extent[0][1]) / spacing),
      static_cast<int>((position[2] - extent[0][2]) / spacing)
    };
    std::string gridIndexKey = std::to_string(gridIndex[0]) + "|" +
                               std::to_string(gridIndex[1]) + "|" +
                               std::to_string(gridIndex[0]);

    // Get grid cell point (if existing)
    LASpoint& gridPoint = grid[gridIndexKey];
    if (gridPoint.point == nullptr) {
      // No point in grid cell -> insert first point
      gridPoint.init(&lasReader->header,
                     lasReader->header.point_data_format,
                     lasReader->header.point_data_record_length,
                     &lasReader->header);
      gridPoint = lasReader->point; // copy assignment
    } else {
      // Get center point of grid cell
      Point cellCenter = {
        gridIndex[0] * spacing + 0.5 * spacing + extent[0][0],
        gridIndex[1] * spacing + 0.5 * spacing + extent[0][1],
        gridIndex[2] * spacing + 0.5 * spacing + extent[0][2]
      };

      Point gridPointPosition{ gridPoint.get_x(),
                               gridPoint.get_y(),
                               gridPoint.get_z() };

      // Compute distance to grid cell center
      double distanceGridPoint =
        sqrt(std::pow(gridPointPosition[0] - cellCenter[0], 2) +
             pow(gridPointPosition[1] - cellCenter[1], 2) +
             pow(gridPointPosition[2] - cellCenter[2], 2));

      double distanceNewPoint = sqrt(pow(position[0] - cellCenter[0], 2) +
                                     pow(position[1] - cellCenter[1], 2) +
                                     pow(position[2] - cellCenter[2], 2));

      if (distanceNewPoint < distanceGridPoint) {
        // Replace point in grid cell
        grid[gridIndexKey] = lasReader->point; // copy assignment
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
  LASwriteOpener lasWriteOpener;
  lasWriteOpener.set_file_name(fileOut.c_str());
  std::memset(lasReader->header.system_identifier, '\0', 32);
  std::memcpy(lasReader->header.system_identifier, "Desktop", 8);
  std::memset(lasReader->header.generating_software, '\0', 32);
  std::memcpy(lasReader->header.generating_software, "SpatiumGL", 10);
  std::unique_ptr<LASwriter> lasWriter(lasWriteOpener.open(&lasReader->header));
  for (const auto& gridCell : grid) {
    lasWriter->write_point(&gridCell.second);
    lasWriter->update_inventory(&gridCell.second);
  }
  lasWriter->update_header(&lasReader->header, TRUE);
  lasWriter->close();

  lasReader->close();

  return 0;
}
