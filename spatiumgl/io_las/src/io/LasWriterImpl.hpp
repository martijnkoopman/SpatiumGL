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

#ifndef SPATIUMGL_IO_LAS_LASWRITERIMPL_H
#define SPATIUMGL_IO_LAS_LASWRITERIMPL_H

#include "spatiumgl/gfx3d/PointCloud.hpp"

#include "laswriter.hpp" // LASlib

namespace spgl {
namespace io {

/// \class LasWriterImpl
/// \brief Write point cloud to LAS/LAZ file.
class LasWriterImpl
{
public:
  /// Constructor
  ///
  /// \param[in] path Path to LAS/LAZ file
  LasWriterImpl(const std::string& path = "");


  ~LasWriterImpl();

  /// Set path to file.
  ///
  /// \param[in] path Path to LAS/LAZ file
  void setPath(const std::string& path);

  /// Get path to file.
  ///
  /// \return Path to LAS/LAZ file
  std::string path() const;

  bool isActive() const;

  bool writePointCloud(const gfx3d::PointCloud& pointCloud);

private:
  LASwriteOpener m_laswriteopener;
};
} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASWRITERIMPL_H
