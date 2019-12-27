#include "CLI11.hpp"

#include "lasreader.hpp" // LASlib

#include <unordered_map> // std::unordered_map

struct LasPoint
{
  double x;
  double y;
  double z;
  unsigned short intensity;
  // unsigned char return_number;
  unsigned char number_of_returns;
  float scan_angle;
  unsigned char user_data;
  unsigned short point_source_id;
  // unsigned char classification;
  double gps_time;
  unsigned short red;
  unsigned short green;
  unsigned short blue;
  unsigned short nir;
};

class LasPointStatistics
{
public:
  LasPointStatistics(const LASheader& lasHeader)
    : m_firstPoint(true)
    , m_pointDataFormat(lasHeader.point_data_format)
    , m_classifications()
    , m_return_numbers()
  {}

  void update(const LASpoint& point)
  {
    if (m_firstPoint) {
      m_firstPoint = false;
      // First point

      m_min.x = m_max.x = point.get_x();
      m_min.y = m_max.y = point.get_y();
      m_min.z = m_max.z = point.get_z();
      m_min.intensity = m_max.intensity = point.get_intensity();
      m_min.number_of_returns = m_max.number_of_returns =
        point.get_number_of_returns();
      m_min.scan_angle = m_max.scan_angle = point.get_scan_angle();
      m_min.user_data = m_max.user_data = point.get_user_data();
      m_min.point_source_id = m_max.point_source_id =
        point.get_point_source_ID();

      // Update tables
      unsigned char return_number = point.get_return_number();
      if (m_return_numbers.find(return_number) == m_return_numbers.end()) {
        m_return_numbers[return_number] = 1;
      } else {
        m_return_numbers[return_number] = m_return_numbers[return_number] + 1;
      }

      unsigned char classification = point.get_classification();
      if (m_classifications.find(classification) == m_classifications.end()) {
        m_classifications[classification] = 1;
      } else {
        m_classifications[classification] =
          m_classifications[classification] + 1;
      }

      if (point.have_gps_time) {
        // Point data format = 1,3,4,6,7,8,9
        m_min.gps_time = m_max.gps_time = point.get_gps_time();
      }
      if (point.have_rgb) {
        // Point data format = 2,3,5,7,8,10
        m_min.red = m_max.red = point.get_R();
        m_min.green = m_max.green = point.get_G();
        m_min.blue = m_max.blue = point.get_B();
      }
      if (point.have_nir) {
        // Point data format = 8
        m_min.nir = m_max.nir = point.get_NIR();
      }
    } else {
      // 2nd or Nth point
      // Update min and max
      m_min.x = std::min(m_min.x, point.get_x());
      m_max.x = std::max(m_max.x, point.get_x());
      m_min.y = std::min(m_min.y, point.get_y());
      m_max.y = std::max(m_max.y, point.get_y());
      m_min.z = std::min(m_min.z, point.get_z());
      m_max.z = std::max(m_max.z, point.get_z());
      m_min.intensity = std::min(m_min.intensity, point.get_intensity());
      m_max.intensity = std::max(m_max.intensity, point.get_intensity());
      m_min.number_of_returns =
        std::min(m_min.number_of_returns, point.get_number_of_returns());
      m_max.number_of_returns =
        std::max(m_max.number_of_returns, point.get_number_of_returns());
      m_min.scan_angle = std::min(m_min.scan_angle, point.get_scan_angle());
      m_max.scan_angle = std::max(m_max.scan_angle, point.get_scan_angle());
      m_min.user_data = std::min(m_min.user_data, point.get_user_data());
      m_max.user_data = std::max(m_max.user_data, point.get_user_data());
      m_min.point_source_id =
        std::min(m_min.point_source_id, point.get_point_source_ID());
      m_max.point_source_id =
        std::max(m_max.point_source_id, point.get_point_source_ID());

      if (point.have_gps_time) {
        // Point data format = 1,3,4,6,7,8,9
        m_min.gps_time = std::min(m_min.gps_time, point.get_gps_time());
        m_max.gps_time = std::max(m_max.gps_time, point.get_gps_time());
      }
      if (point.have_rgb) {
        // Point data format = 2,3,5,7,8,10
        m_min.red = std::min(m_min.red, point.get_R());
        m_max.red = std::max(m_max.red, point.get_R());
        m_min.green = std::min(m_min.green, point.get_G());
        m_max.green = std::max(m_max.green, point.get_G());
        m_min.blue = std::min(m_min.blue, point.get_B());
        m_max.blue = std::max(m_max.blue, point.get_B());
      }
      if (point.have_nir) {
        // Point data format = 8
        m_min.nir = std::min(m_min.nir, point.get_NIR());
        m_max.nir = std::max(m_max.nir, point.get_NIR());
      }

      // Update tables
      unsigned char return_number = point.get_return_number();
      if (m_return_numbers.find(return_number) == m_return_numbers.end()) {
        m_return_numbers[return_number] = 1;
      } else {
        m_return_numbers[return_number] = m_return_numbers[return_number] + 1;
      }

      unsigned char classification = point.get_classification();
      if (m_classifications.find(classification) == m_classifications.end()) {
        m_classifications[classification] = 1;
      } else {
        m_classifications[classification] =
          m_classifications[classification] + 1;
      }
    }
  }

  void print()
  {
    std::cout << "# Point Statistics: " << std::endl;
    std::cout << "X: " << std::to_string(m_min.x) << " - "
              << std::to_string(m_max.x) << std::endl;
    std::cout << "Y: " << std::to_string(m_min.y) << " - "
              << std::to_string(m_max.y) << std::endl;
    std::cout << "Z: " << std::to_string(m_min.z) << " - "
              << std::to_string(m_max.z) << std::endl;

    if (m_min.intensity != m_max.intensity) {
      std::cout << "Intensity: " << std::to_string(m_min.intensity) << " - "
                << std::to_string(m_max.intensity) << std::endl;
    }

    if (m_min.number_of_returns != m_max.number_of_returns) {
      std::cout << "Number of Returns: "
                << std::to_string(m_min.number_of_returns) << " - "
                << std::to_string(m_max.number_of_returns) << std::endl;
    }

    if (m_return_numbers.size() > 1) {
      std::cout << "Return Numbers: " << std::endl;
      for (const auto& pair : m_return_numbers) {
        std::cout << "> " << std::to_string(pair.first) << ": "
                  << std::to_string(pair.second) << std::endl;
      }
    }

    if (m_min.scan_angle != m_max.scan_angle) {
      std::cout << "Scan Angle: " << std::to_string(m_min.scan_angle) << " - "
                << std::to_string(m_max.scan_angle) << std::endl;
    }

    if (m_min.user_data != m_max.user_data) {
      std::cout << "User Data: " << std::to_string(m_min.user_data) << " - "
                << std::to_string(m_max.user_data) << std::endl;
    }

    /// \todo Hash map
    if (m_min.point_source_id != m_max.point_source_id) {
      std::cout << "Point Source ID: " << std::to_string(m_min.point_source_id)
                << " - " << std::to_string(m_max.point_source_id) << std::endl;
    }

    if (m_classifications.size() > 0) {
      std::cout << "Classifications: " << std::endl;
      for (const auto& pair : m_classifications) {
        std::cout << "> " << std::to_string(pair.first) << " ("
                  << classificationToString(pair.first, m_pointDataFormat)
                  << "): " << std::to_string(pair.second) << std::endl;
      }
    }

    if (m_min.gps_time != m_max.gps_time) {
      std::cout << "GPS Time: " << std::to_string(m_min.gps_time) << " - "
                << std::to_string(m_max.gps_time) << std::endl;
    }

    if (m_min.red != m_max.red) {
      std::cout << "Red: " << std::to_string(m_min.red) << " - "
                << std::to_string(m_max.red) << std::endl;
      std::cout << "Green: " << std::to_string(m_min.green) << " - "
                << std::to_string(m_max.green) << std::endl;
      std::cout << "Blue: " << std::to_string(m_min.blue) << " - "
                << std::to_string(m_max.blue) << std::endl;
    }

    if (m_min.nir != m_max.nir) {
      std::cout << "NIR: " << std::to_string(m_min.nir) << " - "
                << std::to_string(m_max.nir) << std::endl;
    }
  }

  static std::string
  classificationToString(unsigned char classification,
                         unsigned char point_data_format)
  {
    if (point_data_format < 6) {
      switch (classification) {
        case 0:
          return "Never classified";
        case 1:
          return "Unclassified";
        case 2:
          return "Ground";
        case 3:
          return "Low Vegetation";
        case 4:
          return "Medium Vegetation";
        case 5:
          return "High Vegetation";
        case 6:
          return "Building";
        case 7:
          return "Low Point (noise)";
        case 8:
          return "Model Key-point (mass point)";
        case 9:
          return "Water";
        case 12:
          return "Overlap Points";
        case 10:
        case 11:
        default:
          return "Reserved";
      }
    } else {
      switch (classification) {
        case 0:
          return "Never classified";
        case 1:
          return "Unclassified";
        case 2:
          return "Ground";
        case 3:
          return "Low Vegetation";
        case 4:
          return "Medium Vegetation";
        case 5:
          return "High Vegetation";
        case 6:
          return "Building";
        case 7:
          return "Low Point (noise)";
        case 8:
          return "Model Key-point (mass point)";
        case 9:
          return "Water";
        case 10:
          return "Rail";
        case 11:
          return "Road Surface";
        case 12:
          return "Reserved";
        case 13:
          return "Wire - Guard (Shield)";
        case 14:
          return "Wire - Conductor (Phase)";
        case 15:
          return "Transmission Tower";
        case 16:
          return "Wire-structure Connector";
        case 17:
          return "Bridge Deck";
        case 18:
          return "High Noise";
      }
      if (classification > 17 && classification < 64) {
        return "Reserved";
      } else {
        return "User defined";
      }
    }
  }

private:
  bool m_firstPoint;
  unsigned char m_pointDataFormat;
  LasPoint m_min;
  LasPoint m_max;
  std::unordered_map<unsigned char, long> m_classifications;
  std::unordered_map<unsigned char, long> m_return_numbers;
};

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
            << std::string(lasReader->header.generating_software) << std::endl;
  std::cout << "File Creation Year-Day: "
            << std::to_string(lasReader->header.file_creation_year) << "-"
            << std::to_string(lasReader->header.file_creation_day) << std::endl;
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
            << std::to_string(lasReader->header.point_data_format) << std::endl;
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
              << std::to_string(
                   lasReader->header.number_of_extended_variable_length_records)
              << "):" << std::endl;
  }

  std::cout << std::endl
            << "Computing point statistics. This may take a while."
            << std::endl;

  LasPointStatistics pointStatistics(lasReader->header);

  // Read all other points
  int progressPercentage = 0;
  long long onePercent = lasReader->header.number_of_point_records / 100;
  long long pointsProcessed = 0;

  // Read point
  while (lasReader->read_point()) {

    // Update statistics
    pointStatistics.update(lasReader->point);

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

  pointStatistics.print();

  lasReader->close();

  return 0;
}
