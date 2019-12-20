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

#include "LasReadTaskImpl.hpp"

namespace spgl {
namespace io {

LasReadTaskImpl::LasReadTaskImpl(const std::string& path, const bool shiftToOrigin)
  : m_lasreadopener()
  , m_reader(nullptr)
  , m_shiftToOrigin(shiftToOrigin)
{
  m_lasreadopener.set_file_name(path.c_str());
}

LasReadTaskImpl::~LasReadTaskImpl()
{
  if (m_reader != nullptr) {
    close();
  }
}

//void LasReadTaskImpl::setPath(const std::string& path)
//{
//  m_lasreadopener.set_file_name(path.c_str());
//}

std::string LasReadTaskImpl::path() const { return m_lasreadopener.get_file_name(); }

bool LasReadTaskImpl::isReady() const { return m_lasreadopener.active(); }

bool LasReadTaskImpl::open()
{
  close();

  m_reader.reset(m_lasreadopener.open());
  return (m_reader != nullptr);
}

bool LasReadTaskImpl::isOpen() const { return (m_reader != nullptr); }

void LasReadTaskImpl::close()
{
  if (m_reader != nullptr) {
    m_reader->close();
    m_reader.reset();
  }
}

 bool LasReadTaskImpl::readPoint()
{
  if (m_reader == nullptr)
  {
    return false;
  }

  return m_reader->read_point();
}

Vector3 LasReadTaskImpl::lastReadPointPosition()
{
  if (m_reader == nullptr)
  {
    return {};
  }

  double x = m_reader->point.get_x();
  double y = m_reader->point.get_y();
  double z = m_reader->point.get_z();

  if (m_shiftToOrigin) {
    x -= m_reader->get_min_x();
    y -= m_reader->get_min_y();
    z -= m_reader->get_min_z();
  }

  return { x, y, z };
}

Vector3 LasReadTaskImpl::lastReadPointColor()
{
  if (m_reader == nullptr)
  {
    return {};
  }

  /// \todo divider by file header
  double r = static_cast<double>(m_reader->point.get_R()) / 255.0 / 255;
  double g = static_cast<double>(m_reader->point.get_G()) / 255.0 / 255;
  double b = static_cast<double>(m_reader->point.get_B()) / 255.0 / 255;

  return { r, g, b };
}

long long int LasReadTaskImpl::pointCount() const
{
  if (m_reader == nullptr) {
    return 0;
  }

  return m_reader->npoints;
}

bool LasReadTaskImpl::hasColors() const
{
  if (m_reader == nullptr) {
    return false;
  }

  const unsigned char format =
    m_reader->header.point_data_format; // get_format();
  return (format == 2 || format == 3 || format == 5 || format == 7 ||
          format == 8 || format == 10);
}

BoundingBox<double> LasReadTaskImpl::extent() const
{
  if (m_reader == nullptr) {
    return {};
  }

  return BoundingBox<double>::fromMinMax(
    { m_reader->get_min_x(), m_reader->get_min_y(), m_reader->get_min_z() },
    { m_reader->get_max_x(), m_reader->get_max_y(), m_reader->get_max_z() });
}

Vector3
LasReadTaskImpl::originShift() const
{
  if (m_reader == nullptr) {
    return {};
  }

  return { m_reader->get_min_x(),
           m_reader->get_min_y(),
           m_reader->get_min_z() };
}

} // namespace io
} // namespace spgl
