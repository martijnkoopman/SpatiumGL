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

namespace spgl {
namespace io {

LasReader::LasReader(const std::string& path)
  : m_pimpl{ std::unique_ptr<LasReaderImpl>(
      new LasReaderImpl(path)) }
{}

// Destructor implementation must be in CPP file for PIMPL pattern
LasReader::~LasReader() = default;

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

void
LasReader::close()
{
  m_pimpl->close();
}

const LasHeader&
LasReader::lasHeader() const
{
  return m_pimpl->lasHeader();
}

const LasPointStatistics&
LasReader::lasPointStatistics() const
{
  return m_pimpl->lasPointStatistics();
}

bool
LasReader::readLasPoint()
{
  return m_pimpl->readLasPoint();
}

const LasPoint&
LasReader::lasPoint() const
{
  return m_pimpl->lasPoint();
}

} // namespace io
} // namespace spgl
