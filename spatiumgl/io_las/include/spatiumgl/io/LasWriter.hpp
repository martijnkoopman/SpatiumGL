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

#ifndef SPATIUMGL_IO_LAS_LASWRITER_H
#define SPATIUMGL_IO_LAS_LASWRITER_H

#include "spatiumgl/gfx3d/PointCloud.hpp"
#include "spatiumglexport.hpp"

#include <memory> // std::unique_ptr

namespace spgl {
namespace io {

// Forward declare implementation
class LasWriterImpl;

/// \class PointCloudWriter
/// \brief Write point cloud to LAS/LAZ file.
class SPATIUMGL_EXPORT LasWriter
{
public:
  /// Constructor
  ///
  /// \param[in] path Path to LAS/LAZ file
  LasWriter(const std::string& path = "");

  /// Destructor
  virtual ~LasWriter(); // Must be virtual for PIMPL pattern

  /// Set path to file.
  ///
  /// \param[in] path Path to LAS/LAZ file
  void setPath(const std::string& path);

  /// Get path to file.
  ///
  /// \return Path to LAS/LAZ file
  std::string path() const;

  /// ???
  ///
  /// \return True if ready, false otherwise
  bool isReady() const;

  /// Read all points from file into a point cloud.
  ///
  /// \return PointCloud
  bool writePointCloud(const gfx3d::PointCloud& pointCloud) const;

private:
  std::unique_ptr<LasWriterImpl> m_pimpl;
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASWRITER_H
