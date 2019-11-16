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

namespace spatiumgl {
namespace io {

LasReaderImpl::LasReaderImpl(const std::string& path, const bool shiftToOrigin)
  : m_lasreadopener()
  , m_reader(nullptr)
  , m_shiftToOrigin(shiftToOrigin)
{
  m_lasreadopener.set_file_name(path.c_str());
}

LasReaderImpl::~LasReaderImpl()
{
  if (m_reader != nullptr) {
    close();
  }
}

void LasReaderImpl::setPath(const std::string& path)
{
  m_lasreadopener.set_file_name(path.c_str());
}

std::string LasReaderImpl::path() const { return m_lasreadopener.get_file_name(); }

bool LasReaderImpl::isReady() const { return m_lasreadopener.active(); }

bool LasReaderImpl::open()
{
  close();

  m_reader = m_lasreadopener.open();
  return (m_reader != nullptr);
}

bool LasReaderImpl::isOpen() const { return (m_reader != nullptr); }

void LasReaderImpl::close()
{
  if (m_reader != nullptr) {
    m_reader->close();
    delete m_reader;
    m_reader = nullptr;
  }
}

// bool readSinglePoint()
//{
//	if (m_reader == nullptr)
//	{
//		return false;
//	}

//	return m_reader->read_point();
//}

// Vector3 lastReadPointPosition()
//{
//	if (m_reader == nullptr)
//	{
//		return Vector3(0, 0, 0);
//	}

//	double x = m_reader->point.get_x();
//	double y = m_reader->point.get_y();
//	double z = m_reader->point.get_z();
//	return Vector3(x, y, z);
//}

// Vector3 lastReadPointColor()
//{
//	if (m_reader == nullptr)
//	{
//		return Vector3(0, 0, 0);
//	}

//	double r = static_cast<double>(m_reader->point.get_R()) / 0xFFFF;
//	double g = static_cast<double>(m_reader->point.get_G()) / 0xFFFF;
//	double b = static_cast<double>(m_reader->point.get_B()) / 0xFFFF;

//	return Vector3(r, g, b);
//}

gfx3d::PointCloud LasReaderImpl::readAllPoints()
{
  if (m_reader == nullptr) {
    return gfx3d::PointCloud();
  } else {
    const double x_min = m_reader->get_min_x();
    const double y_min = m_reader->get_min_y();
    const double z_min = m_reader->get_min_z();

    const bool hasColor = hasColors();
    gfx3d::PointCloud pointCloud(m_reader->npoints, hasColor);
    if (m_shiftToOrigin) {
      pointCloud.setShift({ x_min, y_min, z_min });
    }

    while (m_reader->read_point()) {
      double x = m_reader->point.get_x();
      double y = m_reader->point.get_y();
      double z = m_reader->point.get_z();

      if (m_shiftToOrigin) {
        x -= x_min;
        y -= y_min;
        z -= z_min;
      }

      if (hasColor) {
        double r = static_cast<double>(m_reader->point.get_R()) / 255;
        double g = static_cast<double>(m_reader->point.get_G()) / 255;
        double b = static_cast<double>(m_reader->point.get_B()) / 255;

        pointCloud.addPoint({ x, y, z }, { r, g, b });
      } else {
        pointCloud.addPoint({ x, y, z });
      }
    }
    return pointCloud;
  }
}

long long int LasReaderImpl::pointCount() const
{
  if (m_reader == nullptr) {
    return 0;
  }

  return m_reader->npoints;
}

bool LasReaderImpl::hasColors() const
{
  if (m_reader == nullptr) {
    return false;
  }

  const unsigned char format =
    m_reader->header.point_data_format; // get_format();
  return (format == 2 || format == 3 || format == 5 || format == 7 ||
          format == 8 || format == 10);
}

bool LasReaderImpl::hasNormals() const
{
  if (m_reader == nullptr) {
    return false;
  }

  return false;
}

BoundingBox<double> LasReaderImpl::bounds() const
{
  if (m_reader == nullptr) {
    return {};
  }

  return BoundingBox<double>::fromMinMax(
    { m_reader->get_min_x(), m_reader->get_min_y(), m_reader->get_min_z() },
    { m_reader->get_max_x(), m_reader->get_max_y(), m_reader->get_max_z() });
}

} // namespace io
} // namespace spatiumgl
