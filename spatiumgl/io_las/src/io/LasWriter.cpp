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

#include "spatiumgl/io/LasWriter.hpp"
#include "LasWriterImpl.hpp"

namespace spgl {
namespace io {

LasWriter::LasWriter(const std::string& path)
  : m_pimpl{ std::unique_ptr<LasWriterImpl>(new LasWriterImpl(path)) }
{}

// Destructor implementation must be in CPP file for PIMPL pattern
LasWriter::~LasWriter() = default;

std::string
LasWriter::path() const
{
  return m_pimpl->path();
}

bool
LasWriter::isReady() const
{
  return m_pimpl->isReady();
}

bool
LasWriter::open(const LasHeader& lasHeader)
{
  return m_pimpl->open(lasHeader);
}

bool
LasWriter::isOpen()
{
  return m_pimpl->isOpen();
}

void
LasWriter::close()
{
  m_pimpl->close();
}

void LasWriter::writeLasPoint(const LasPoint& point)
{
  m_pimpl->writeLasPoint(point);
}


} // namespace io
} // namespace spgl
