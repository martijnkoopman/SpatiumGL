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

#ifndef SPATIUMGL_IO_LAS_LASREADERIMPL_H
#define SPATIUMGL_IO_LAS_LASREADERIMPL_H

#include "spatiumgl/gfx3d/PointCloud.hpp"

#include "lasreader.hpp" // LASlib

namespace spatiumgl {
namespace io {

/// \class LasReaderImpl
/// \brief Read point cloud from LAS/LAZ file.
class LasReaderImpl
{
public:
  LasReaderImpl(const std::string& path, const bool shiftToOrigin);

  ~LasReaderImpl();

  void setPath(const std::string& path);

  std::string path() const;

  bool isReady() const;
  bool open();

  bool isOpen() const;

  void close();

  gfx3d::PointCloud readAllPoints();

  long long int pointCount() const;

  bool hasColors() const;

  bool hasNormals() const;

  BoundingBox<double> bounds() const;

private:
  LASreadOpener m_lasreadopener;
  LASreader* m_reader;
  bool m_shiftToOrigin;
};

} // namespace io
} // namespace spatiumgl

#endif // SPATIUMGL_IO_LAS_LASREADERIMPL_H
