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

#include "LasWriterImpl.hpp"

#include <memory> // std::unique_ptr

namespace spatiumgl {
namespace io {
LasWriterImpl::LasWriterImpl(const std::string& path)
  : m_laswriteopener()
{
  m_laswriteopener.set_file_name(path.c_str());
}

LasWriterImpl::~LasWriterImpl() {}

void
LasWriterImpl::setPath(const std::string& path)
{
  m_laswriteopener.set_file_name(path.c_str());
}

std::string
LasWriterImpl::path() const
{
  return m_laswriteopener.get_file_name();
}

bool
LasWriterImpl::isActive() const
{
  return m_laswriteopener.active();
}

bool
LasWriterImpl::writePointCloud(const gfx3d::PointCloud& pointCloud)
{
  const bool hasColors = pointCloud.header().hasColors();
  // const bool hasNormals = pointCloud.hasNormals();

  // Init header
  LASheader lasheader;
  lasheader.x_scale_factor = 0.01;
  lasheader.y_scale_factor = 0.01;
  lasheader.z_scale_factor = 0.01;
  lasheader.x_offset = 0;
  lasheader.y_offset = 0;
  lasheader.z_offset = 0;
  lasheader.point_data_format = (hasColors ? 2 : 0); // See LAS specification
  lasheader.point_data_record_length = (hasColors ? 26 : 20);

  // Init point
  LASpoint laspoint;
  laspoint.init(&lasheader,
                lasheader.point_data_format,
                lasheader.point_data_record_length,
                nullptr);

  // Open laswriter
  std::unique_ptr<LASwriter> laswriter(m_laswriteopener.open(&lasheader));
  if (laswriter == nullptr) {
    return false;
  }

  for (size_t i = 0; i < pointCloud.header().pointCount(); i++) {
    // Populate the point
    Vector3 position = pointCloud.data().positions()[i] + pointCloud.header().originShift();
    laspoint.set_X(static_cast<int>(position.x() * 100));
    laspoint.set_Y(static_cast<int>(position.y() * 100));
    laspoint.set_Z(static_cast<int>(position.z() * 100));
    if (hasColors) {
      Vector3 color = pointCloud.data().colors()[i];
      laspoint.set_R(static_cast<unsigned short>(color.x() * 255));
      laspoint.set_G(static_cast<unsigned short>(color.y() * 255));
      laspoint.set_B(static_cast<unsigned short>(color.z() * 255));
    }

    // Write the point
    laswriter->write_point(&laspoint);

    // Add it to the inventory
    laswriter->update_inventory(&laspoint);
  }

  // Update the header
  laswriter->update_header(&lasheader, TRUE);

  // close the writer
  laswriter->close();

  return true;
}
} // namespace io
} // namespace spatiumgl