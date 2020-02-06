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

#include "LasReaderImpl.hpp"
#include "spatiumgl/io/LasUtils.hpp"

namespace spgl {
namespace io {

LasReaderImpl::LasReaderImpl(const std::string& path)
  : m_lasReadOpener()
  , m_lasReader(nullptr)
  , m_header()
  , m_pointStatistics(0)
  , m_point()
{
  m_lasReadOpener.set_file_name(path.c_str());
}

LasReaderImpl::~LasReaderImpl()
{
  if (m_lasReader != nullptr) {
    close();
  }
}

std::string LasReaderImpl::path() const { return m_lasReadOpener.get_file_name(); }

bool LasReaderImpl::isReady() const { return m_lasReadOpener.active(); }

bool LasReaderImpl::open()
{
  close();

  // Open file
  m_lasReader.reset(m_lasReadOpener.open());

  if (m_lasReader != nullptr) {
    // Read header
    m_header.point_data_format = m_lasReader->header.point_data_format;
    m_header.number_of_point_records = m_lasReader->npoints;
    m_header.scale_factor =
      std::min(m_lasReader->header.x_scale_factor,
               std::min(m_lasReader->header.y_scale_factor,
                        m_lasReader->header.z_scale_factor));
    m_header.compressed = m_lasReader->header.is_compressed();
    m_header.extent = BoundingBox::fromMinMax(
      { m_lasReader->get_min_x(), m_lasReader->get_min_y(), m_lasReader->get_min_z() },
      { m_lasReader->get_max_x(), m_lasReader->get_max_y(), m_lasReader->get_max_z() });
    return true;
  } else {
    return false;
  }
}

bool LasReaderImpl::isOpen() const { return (m_lasReader != nullptr); }

void LasReaderImpl::close()
{
  if (m_lasReader != nullptr) {
    m_lasReader->close();
    m_lasReader.reset();
    m_lasReadOpener.reset();
  }
}

const LasHeader& LasReaderImpl::lasHeader() const { return m_header; }

const LasPointStatistics& LasReaderImpl::lasPointStatistics() const
{
  return m_pointStatistics;
}

 bool LasReaderImpl::readLasPoint()
{
  if (m_lasReader == nullptr)
  {
    return false;
  }

  bool ret = m_lasReader->read_point();
  if (ret) {
    // Read point fields
    m_point.xyz[0] = m_lasReader->point.get_x() - m_lasReader->get_min_x();
    m_point.xyz[2] = m_lasReader->point.get_y() - m_lasReader->get_min_y();
    m_point.xyz[1] = m_lasReader->point.get_z() - m_lasReader->get_min_z();
    m_point.intensity = m_lasReader->point.get_intensity();
    m_point.return_number = m_lasReader->point.get_return_number();
    m_point.number_of_returns = m_lasReader->point.get_number_of_returns();
    m_point.classification = m_lasReader->point.get_classification();
    m_point.scan_angle_rank = m_lasReader->point.get_scan_angle_rank();
    m_point.user_data = m_lasReader->point.get_user_data();
    m_point.point_source_ID = m_lasReader->point.get_point_source_ID();

    if (LasUtils::formatHasGpsTime(m_header.point_data_format)) {
      m_point.gps_time = m_lasReader->point.get_gps_time();
    }

    if (LasUtils::formatHasRgb(m_header.point_data_format)) {
      m_point.rgb[0] = m_lasReader->point.get_R();
      m_point.rgb[1] = m_lasReader->point.get_G();
      m_point.rgb[2] = m_lasReader->point.get_B();
    }

    if (LasUtils::formatHasNir(m_header.point_data_format)) {
      m_point.nir = m_lasReader->point.get_NIR();
    }

    // Update point statistics
    m_pointStatistics.addLasPoint(m_point);
  }
  return ret;
}

const LasPoint&
LasReaderImpl::lasPoint() const
{
  return m_point;
}

} // namespace io
} // namespace spgl
