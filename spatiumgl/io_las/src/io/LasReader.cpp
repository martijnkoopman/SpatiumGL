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

#include "spatiumgl/io/LasReader.hpp"
#include "LasReaderImpl.hpp"

namespace spatiumgl {
namespace io {

LasReader::LasReader(const std::string& path, const bool shiftToOrigin)
  : m_pimpl{ std::unique_ptr<LasReaderImpl>(new LasReaderImpl(path, shiftToOrigin)) }
{}

LasReader::~LasReader() = default;

void
LasReader::setPath(const std::string& path)
{
  m_pimpl->setPath(path);
}

std::string
LasReader::path() const
{
  return m_pimpl->path();
}

bool
LasReader::isReady() const
{
  return m_pimpl->isReady();
}

bool
LasReader::open()
{
  return m_pimpl->open();
}

bool
LasReader::isOpen()
{
  return m_pimpl->isOpen();
}

gfx3d::PointCloud
LasReader::readAllPoints()
{
  return m_pimpl->readAllPoints();
}

void
LasReader::close()
{
  m_pimpl->close();
}

// bool LasReader::readSinglePoint()
//{
//	return m_pimpl->readSinglePoint();
//}

// Vector3 LasReader::lastReadPointPosition()
//{
//	return m_pimpl->lastReadPointPosition();
//}

// Vector3 LasReader::lastReadPointColor()
//{
//	return m_pimpl->lastReadPointColor();
//}

long long int
LasReader::pointCount() const
{
  return m_pimpl->pointCount();
}

bool
LasReader::hasColors() const
{
  return m_pimpl->hasColors();
}

bool
LasReader::hasNormals() const
{
  return m_pimpl->hasNormals();
}

BoundingBox<double>
LasReader::bounds() const
{
  return m_pimpl->bounds();
}
} // namespace io
} // namespace spatiumgl
