#include "CLI11.hpp"

#include "LasOctant.hpp"
#include <spatiumgl/idx/NTree.hpp>

#include "lasreader.hpp" // LASlib

#include <algorithm> // std::max
#include <array>     // std::array
#include <queue>     // std::queue
#include <tuple>	   // std::tuple

int
main(int argc, char* argv[])
{
  // Parse command-line arguments
  CLI::App app{"Create spatial index for viewing a massive point cloud in 3D."};

  std::string fileIn;
  app.add_option("-i,--input", fileIn, "Input LAS/lAZ file")
    ->required()
    ->check(CLI::ExistingFile);

  std::string dirOut;
  app.add_option("-o,--output", dirOut, "Output directory")
    ->required()
    ->check(CLI::ExistingDirectory);

  int targetPointCount;
  app
    .add_option("-n,--num", targetPointCount, "Target number of points per node")
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

  // Compute spacing
  const double w = (lasReader->header.max_x - lasReader->header.min_x);
  const double l = (lasReader->header.max_y - lasReader->header.min_y);
  const double h = (lasReader->header.max_z - lasReader->header.min_z);
  const double spacing = cbrt((w * l * h) / targetPointCount); // Try: diagonal /250

  // Compute octree extent
  const double radius = std::max({ w, l, h }) / 2;
  Point center{ (lasReader->header.max_x + lasReader->header.min_x) / 2,
                (lasReader->header.max_y + lasReader->header.min_y) / 2,
                (lasReader->header.max_z + lasReader->header.min_z) / 2 };
  Extent extent{
    Point{ center[0] - radius, center[1] - radius, center[2] - radius },
    Point{ center[0] + radius, center[1] + radius, center[2] + radius }
  };

  // Close input file for now
  lasReader->close();
  lasReader.reset(nullptr);

  // Process root node
  LasOctant octant(fileIn, dirOut + "\\r.las"); // Windows backslash!
  if (!octant.isOpen()) {
    return 1;
  }
  std::array<long long, 8> childPointCounts = octant.process(extent, spacing);

  // Push first children on queue
  std::queue<std::tuple<std::string,Extent,double>> queue;
  for (size_t i = 0; i < 8; i++) {
    if (childPointCounts[i] > targetPointCount) {
      queue.push({ LasOctant::computeFilePath(octant.fileOut(), static_cast<unsigned char>(i)),
                   LasOctant::computeChildExtent(extent, static_cast<unsigned char>(i)),
				   spacing / 2});
	}
  }
  octant.close();

  // Iteratvely process queue
  while (!queue.empty()) {

    // Pop first file from queue
    std::tuple<std::string, Extent,double> item = queue.front();
    queue.pop();
    std::string fileName =  std::get<0>(item);
    Extent extent = std::get<1>(item);
    double spacing = std::get<2>(item);

	// Process octant
    LasOctant octant(fileName);
    if (!octant.isOpen()) {
      std::cerr << "Error opening file " << fileName << std::endl;
      continue;
    }
    std::array<long long, 8> childPointCounts = octant.process(extent, spacing);

	// Push children on queue
    for (size_t i = 0; i < 8; i++) {
      if (childPointCounts[i] > targetPointCount) {
        queue.push({ LasOctant::computeFilePath(octant.fileOut(), static_cast<unsigned char>(i)),
                     LasOctant::computeChildExtent(extent, static_cast<unsigned char>(i)),
					 spacing / 2});
      }
    }
  }

  return 0;
}
