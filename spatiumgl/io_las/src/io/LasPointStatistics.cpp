/*
 * Program: Spatium Graphics Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#include "spatiumgl/io/LasPointStatistics.hpp"
#include "spatiumgl/io/LasUtils.hpp"

#include <algorithm> // std::min, std::max

namespace spgl {
namespace io {

LasPointStatistics::LasPointStatistics(unsigned char pointFormat)
  : m_pointFormat(pointFormat)
  , m_pointCount(0)
  , m_min()
  , m_max()
  , m_classifications()
  , m_return_numbers()
{}

void LasPointStatistics::addLasPoint(const LasPoint& lasPoint)
{
  if (m_pointCount == 0) {
    // Set initial statistics
    m_min.xyz[0] = m_max.xyz[0] = lasPoint.xyz[0];
    m_min.xyz[1] = m_max.xyz[1] = lasPoint.xyz[1];
    m_min.xyz[2] = m_max.xyz[2] = lasPoint.xyz[2];
    m_min.intensity = m_max.intensity = lasPoint.intensity;
    m_min.return_number = m_max.return_number = lasPoint.return_number;
    m_min.number_of_returns = m_max.number_of_returns =
      lasPoint.number_of_returns;
    m_min.classification = m_max.classification = lasPoint.classification;
    m_min.scan_angle_rank = m_max.scan_angle_rank = lasPoint.scan_angle_rank;
    m_min.user_data = m_max.user_data = lasPoint.user_data;
    m_min.point_source_ID = m_max.point_source_ID = lasPoint.point_source_ID;
    m_min.gps_time = m_max.gps_time = lasPoint.gps_time;
    m_min.rgb[0] = m_max.rgb[0] = lasPoint.rgb[0];
    m_min.rgb[1] = m_max.rgb[1] = lasPoint.rgb[1];
    m_min.rgb[2] = m_max.rgb[2] = lasPoint.rgb[2];
    m_min.nir = m_max.nir = lasPoint.nir;

    m_classifications[lasPoint.classification] = 1;
    m_return_numbers[lasPoint.return_number] = 1;
  } else {
    // Upate statistics

    // Update min values
    m_min.xyz[0] = std::min(m_min.xyz[0], lasPoint.xyz[0]);
    m_min.xyz[1] = std::min(m_min.xyz[1], lasPoint.xyz[1]);
    m_min.xyz[2] = std::min(m_min.xyz[2], lasPoint.xyz[2]);
    m_min.intensity = std::min(m_min.intensity, lasPoint.intensity);
    m_min.return_number = std::min(m_min.return_number, lasPoint.return_number);
    m_min.number_of_returns = std::min(m_min.number_of_returns, lasPoint.number_of_returns);
    m_min.classification = std::min(m_min.classification, lasPoint.classification);
    m_min.scan_angle_rank = std::min(m_min.scan_angle_rank, lasPoint.scan_angle_rank);
    m_min.user_data = std::min(m_min.user_data, lasPoint.user_data);
    m_min.point_source_ID = std::min(m_min.point_source_ID, lasPoint.point_source_ID);
    m_min.gps_time = std::min(m_min.gps_time, lasPoint.gps_time);
    m_min.rgb[0] = std::min(m_min.rgb[0], lasPoint.rgb[0]);
    m_min.rgb[1] = std::min(m_min.rgb[1], lasPoint.rgb[1]);
    m_min.rgb[2] = std::min(m_min.rgb[2], lasPoint.rgb[2]);
    m_min.nir = std::min(m_min.nir, lasPoint.nir);

    // Update max values
    m_max.xyz[0] = std::max(m_max.xyz[0], lasPoint.xyz[0]);
    m_max.xyz[1] = std::max(m_max.xyz[1], lasPoint.xyz[1]);
    m_max.xyz[2] = std::max(m_max.xyz[2], lasPoint.xyz[2]);
    m_max.intensity = std::max(m_max.intensity, lasPoint.intensity);
    m_max.return_number = std::max(m_max.return_number, lasPoint.return_number);
    m_max.number_of_returns = std::max(m_max.number_of_returns, lasPoint.number_of_returns);
    m_max.classification = std::max(m_max.classification, lasPoint.classification);
    m_max.scan_angle_rank = std::max(m_max.scan_angle_rank, lasPoint.scan_angle_rank);
    m_max.user_data = std::max(m_max.user_data, lasPoint.user_data);
    m_max.point_source_ID = std::max(m_max.point_source_ID, lasPoint.point_source_ID);
    m_max.gps_time = std::max(m_max.gps_time, lasPoint.gps_time);
    m_max.rgb[0] = std::max(m_max.rgb[0], lasPoint.rgb[0]);
    m_max.rgb[1] = std::max(m_max.rgb[1], lasPoint.rgb[1]);
    m_max.rgb[2] = std::max(m_max.rgb[2], lasPoint.rgb[2]);
    m_max.nir = std::max(m_max.nir, lasPoint.nir);

    // Update classifications map
    if (m_classifications.find(lasPoint.classification) ==
        m_classifications.end()) {
      m_classifications[lasPoint.classification] = 1;
    } else {
      m_classifications[lasPoint.classification] =
        m_classifications[lasPoint.classification] + 1;
    }

    // Update return numbers map
    if (m_return_numbers.find(lasPoint.return_number) ==
        m_return_numbers.end()) {
      m_return_numbers[lasPoint.return_number] = 1;
    } else {
      m_return_numbers[lasPoint.return_number] =
        m_return_numbers[lasPoint.return_number] + 1;
    }
  }

  m_pointCount++;
}

const LasPoint&
LasPointStatistics::min() const
{
  return m_min;
}

const LasPoint&
LasPointStatistics::max() const
{
  return m_max;
}

std::ostream& operator<<(std::ostream& os,
           const LasPointStatistics& stats)
{
  // XYZ
  os << "X: " << std::to_string(stats.m_min.xyz[0]) << " - "
     << std::to_string(stats.m_max.xyz[0]) << std::endl;
  os << "Y: " << std::to_string(stats.m_min.xyz[1]) << " - "
     << std::to_string(stats.m_max.xyz[1]) << std::endl;
  os << "Z: " << std::to_string(stats.m_min.xyz[2]) << " - "
     << std::to_string(stats.m_max.xyz[2]) << std::endl;

  // Intensity
  if (stats.m_min.intensity != 0 || stats.m_max.intensity != 0) {
    os << "Intensity: " << std::to_string(stats.m_min.intensity) << " - "
       << std::to_string(stats.m_max.intensity) << std::endl;
  }

  // Number of returns
  if (stats.m_min.number_of_returns != 0 ||
      stats.m_max.number_of_returns != 0) {
    os << "Number of Returns: "
       << std::to_string(stats.m_min.number_of_returns) << " - "
       << std::to_string(stats.m_max.number_of_returns) << std::endl;
  }

  // Return number
  if (stats.m_return_numbers.size() > 1) {
    os << "Return Numbers: " << std::endl;
    for (const auto& pair : stats.m_return_numbers) {
      os << "> " << std::to_string(pair.first) << ": "
         << std::to_string(pair.second) << std::endl;
    }
  }

  // Classification
  if (stats.m_classifications.size() > 0) {
    os << "Classifications: " << std::endl;
    for (const auto& pair : stats.m_classifications) {
      os << "> " << std::to_string(pair.first) << " ("
         << LasUtils::classificationToString(pair.first,
         stats.m_pointFormat)
         << "): " << std::to_string(pair.second) << std::endl;
    }
  }

  // Scan Angle Rank
  if (stats.m_min.scan_angle_rank != 0 || stats.m_max.scan_angle_rank != 0) {
    os << "Scan Angle Rank: " << std::to_string(stats.m_min.scan_angle_rank)
       << " - " << std::to_string(stats.m_max.scan_angle_rank) << std::endl;
  }

  // User Data
  if (stats.m_min.user_data != 0 || stats.m_max.user_data != 0) {
    os << "User Data: " << std::to_string(stats.m_min.user_data) << " - "
       << std::to_string(stats.m_max.user_data) << std::endl;
  }

  // Point Source ID
  if (stats.m_min.point_source_ID != 0 || stats.m_max.point_source_ID != 0) {
    os << "Point Source ID: " << std::to_string(stats.m_min.point_source_ID)
       << " - " << std::to_string(stats.m_max.point_source_ID) << std::endl;
  }

  // GPS Time
  if (LasUtils::formatHasGpsTime(stats.m_pointFormat)) {
    if (stats.m_min.gps_time != 0 || stats.m_max.gps_time != 0) {
      os << "GPS Time: " << std::to_string(stats.m_min.gps_time) << " - "
         << std::to_string(stats.m_max.gps_time) << std::endl;
    }
  }

  // RGB
  if (LasUtils::formatHasRgb(stats.m_pointFormat)) {
    if (stats.m_min.rgb[0] != 0 || stats.m_max.rgb[0] != 0 ||
        stats.m_min.rgb[1] != 0 || stats.m_max.rgb[1] != 0 ||
        stats.m_min.rgb[2] != 0 || stats.m_max.rgb[2] != 0) {
      os << "Red: " << std::to_string(stats.m_min.rgb[0]) << " - "
         << std::to_string(stats.m_max.rgb[0]) << std::endl;
      os << "Green: " << std::to_string(stats.m_min.rgb[1]) << " - "
         << std::to_string(stats.m_max.rgb[1]) << std::endl;
      os << "Blue: " << std::to_string(stats.m_min.rgb[2]) << " - "
         << std::to_string(stats.m_max.rgb[2]) << std::endl;
    }
  }

  // NIR
  if (LasUtils::formatHasNir(stats.m_pointFormat)) {
    if (stats.m_min.nir != 0 || stats.m_max.nir != 0) {
      os << "NIR: " << std::to_string(stats.m_min.nir) << " - "
         << std::to_string(stats.m_max.nir) << std::endl;
    }
  }

  return os;
}

} // namespace io
} // namespace spgl
