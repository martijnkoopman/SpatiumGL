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
#include "spatiumgl/io/LasUtils.hpp"

#include <memory>  // std::unique_ptr
#include <cstring> // std::strncpy

namespace spgl {
namespace io {
LasWriterImpl::LasWriterImpl(const std::string& path)
  : m_lasWriteOpener()
  , m_lasWriter(nullptr)
  , m_header()
{
  m_lasWriteOpener.set_file_name(path.c_str());
}

LasWriterImpl::~LasWriterImpl() {
  if (m_lasWriter != nullptr) {
    close();
  }
}

std::string
LasWriterImpl::path() const
{
  return m_lasWriteOpener.get_file_name();
}

bool
LasWriterImpl::isReady() const
{
  return m_lasWriteOpener.active();
}

bool
LasWriterImpl::open(const LasHeader& header)
{
  close();

  // Construct LASlib file header
  m_lasHeader.x_scale_factor = header.scale_factor;
  m_lasHeader.y_scale_factor = header.scale_factor;
  m_lasHeader.z_scale_factor = header.scale_factor;
  m_lasHeader.x_offset = header.extent.min()[0];
  m_lasHeader.y_offset = header.extent.min()[1];
  m_lasHeader.z_offset = header.extent.min()[2];
  m_lasHeader.point_data_format = header.point_data_format;
  m_lasHeader.point_data_record_length =
    LasUtils::formatRecordSize(header.point_data_format);
  std::strncpy(m_lasHeader.system_identifier, "Spatium Graphics Library", 32);
  m_lasHeader.system_identifier[31] = '\0';
  strncpy(m_lasHeader.generating_software, "SpatiumGL", 32);
  m_lasHeader.generating_software[31] = '\0';

  /// \todo LASzip compression

  // Init point
  m_lasPoint.init(&m_lasHeader,
                  m_lasHeader.point_data_format,
                  m_lasHeader.point_data_record_length,
                  nullptr);

  // Open file
  m_lasWriter.reset(m_lasWriteOpener.open(&m_lasHeader));
  return (m_lasWriter != nullptr);
}

bool
LasWriterImpl::isOpen() const
{
  return (m_lasWriter != nullptr);
}

void
LasWriterImpl::close()
{
  if (m_lasWriter != nullptr) {
    m_lasWriter->update_header(&m_lasHeader, true);
    m_lasWriter->close();
    m_lasWriter.reset();
  }
}

void
LasWriterImpl::writeLasPoint(const LasPoint& point)
{ 
  // Set point values
  m_lasPoint.set_X(static_cast<int>(point.xyz[0] * (1.0 / m_lasHeader.x_scale_factor)));
  m_lasPoint.set_Y(static_cast<int>(point.xyz[1] * (1.0 / m_lasHeader.y_scale_factor)));
  m_lasPoint.set_Z(static_cast<int>(point.xyz[2] * (1.0 / m_lasHeader.z_scale_factor)));
  m_lasPoint.set_intensity(point.intensity);
  m_lasPoint.set_return_number(point.return_number);
  m_lasPoint.set_number_of_returns(point.number_of_returns);
  m_lasPoint.set_classification(point.classification);
  m_lasPoint.set_scan_angle_rank(point.scan_angle_rank);
  m_lasPoint.set_user_data(point.user_data);
  m_lasPoint.set_point_source_ID(point.point_source_ID);
  if (LasUtils::formatHasGpsTime(m_lasHeader.point_data_format)) {
    m_lasPoint.set_gps_time(point.gps_time);
  }
  if (LasUtils::formatHasRgb(m_lasHeader.point_data_format)) {
    m_lasPoint.set_R(point.rgb[0]);
    m_lasPoint.set_G(point.rgb[1]);
    m_lasPoint.set_B(point.rgb[2]);
  }
  if (LasUtils::formatHasNir(m_lasHeader.point_data_format)) {
    m_lasPoint.set_NIR(point.nir);
  }

  // Write the point
  m_lasWriter->write_point(&m_lasPoint);

  // Add it to the inventory
  m_lasWriter->update_inventory(&m_lasPoint);
}

} // namespace io
} // namespace spgl
