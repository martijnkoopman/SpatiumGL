#include <spatiumgl/io/LasReader.hpp>
#include "CLI11.hpp"

#include "lasreader.hpp" // LASlib

int
main(int argc, char* argv[])
{
  // Parse command-line arguments
  CLI::App app{ "View LAS/LAZ file info." };
  std::string fileIn;
  app.add_option("-i,--input", fileIn, "Input LAS/lAZ file")
    ->required()
    ->check(CLI::ExistingFile);
  CLI11_PARSE(app, argc, argv)

  {
    // Open input file with LASlib for full header info
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

    // Print header information
    std::cout << "# File: " << std::endl;

    std::cout << "File Signature: "
              << std::string(lasReader->header.file_signature) << std::endl;
    std::cout << "File Source ID: "
              << std::to_string(lasReader->header.file_source_ID) << std::endl;
    std::cout << "Version: " << std::to_string(lasReader->header.version_major)
              << "." << std::to_string(lasReader->header.version_minor)
              << std::endl;
    std::cout << "System Identifier: "
              << std::string(lasReader->header.system_identifier) << std::endl;
    std::cout << "Generating Software: "
              << std::string(lasReader->header.generating_software)
              << std::endl;
    std::cout << "File Creation Year-Day: "
              << std::to_string(lasReader->header.file_creation_year) << "-"
              << std::to_string(lasReader->header.file_creation_day)
              << std::endl;
    std::cout << "Compressed: "
              << (lasReader->header.is_compressed() ? "Yes" : "No") << std::endl
              << std::endl;
    std::cout << "# Points: " << std::endl;
    std::cout << "Number of point records: "
              << std::to_string(lasReader->header.number_of_point_records)
              << std::endl;
    std::cout << "Number of points by return (5): ";
    for (int i = 0; i < 4; i++) {
      std::cout << lasReader->header.number_of_points_by_return[i] << ", ";
    }
    std::cout << lasReader->header.number_of_points_by_return[4] << std::endl;

    if (lasReader->header.version_major == 1 &&
        lasReader->header.version_minor > 3) {
      std::cout << "Number of point records (extended): "
                << std::to_string(
                     lasReader->header.extended_number_of_point_records)
                << std::endl;
      std::cout << "Number of points by return (extended, 15): ";
      for (int i = 0; i < 14; i++) {
        std::cout << lasReader->header.extended_number_of_points_by_return[i]
                  << ", ";
      }
      std::cout << lasReader->header.extended_number_of_points_by_return[14]
                << std::endl;
    }
    std::cout << "Point Data Format: "
              << std::to_string(lasReader->header.point_data_format)
              << std::endl;
    std::cout << "Lon-lat: " << (lasReader->header.is_lonlat() ? "Yes" : "No")
              << std::endl;
    std::cout << "Scale Factor: "
              << std::to_string(lasReader->header.x_scale_factor) << " "
              << std::to_string(lasReader->header.y_scale_factor) << " "
              << std::to_string(lasReader->header.z_scale_factor) << std::endl;
    std::cout << "Offset: " << std::to_string(lasReader->header.x_offset) << " "
              << std::to_string(lasReader->header.y_offset) << " "
              << std::to_string(lasReader->header.z_offset) << std::endl;
    std::cout << "Min: " << std::to_string(lasReader->header.min_x) << " "
              << std::to_string(lasReader->header.min_y) << " "
              << std::to_string(lasReader->header.min_z) << std::endl;
    std::cout << "Max: " << std::to_string(lasReader->header.max_x) << " "
              << std::to_string(lasReader->header.max_y) << " "
              << std::to_string(lasReader->header.max_z) << std::endl
              << std::endl;
    std::cout << "# Variable Length Records: "
              << std::to_string(
                   lasReader->header.number_of_variable_length_records)
              << "" << std::endl;
    if (lasReader->header.version_major == 1 &&
        lasReader->header.version_minor > 3) {
      std::cout << "# Extended Variable Length Records ("
                << std::to_string(lasReader->header
                                    .number_of_extended_variable_length_records)
                << "):" << std::endl;
    }

    lasReader->close();
  }

  std::cout << std::endl
            << "Computing point statistics. This may take a while."
            << std::endl;

  {
    // Open file with SpatiumGL LAS reader
    spgl::io::LasReader reader(fileIn);
    if (!reader.isReady()) {
      std::cerr << "Unable to open file." << std::endl;
      return 1;
    }

    if (!reader.open()) {
      std::cerr << "Failed to open file." << std::endl;
      return 1;
    }

    // Read all other points
    int progressPercentage = 0;
    long long onePercent = reader.lasHeader().number_of_point_records / 100;
    long long pointsProcessed = 0;

    // Read point
    while (reader.readLasPoint()) {

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

    std::cout << reader.lasPointStatistics() << std::endl;
    reader.close();
  }

  return 0;
}
