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

#ifndef SPATIUMGL_IO_LAS_LASREADTASK_H
#define SPATIUMGL_IO_LAS_LASREADTASK_H

#include "spatiumgl/AsyncTask.hpp"
#include "spatiumgl/gfx3d/PointCloud.hpp"
#include "spatiumglexport.hpp"

#include <memory> // std::unique_ptr

namespace spatiumgl {
namespace io {

// Forward declare implementation
class LasReadTaskImpl;

/// \class LasReadTask
/// \brief Read point cloud from LAS/LAZ file asynchronously.
///
/// \todo Read normals
class SPATIUMGL_EXPORT LasReadTask : public AsyncTask<gfx3d::PointCloud>
{
public:
  /// Constructor
  ///
  /// \param[in] path Path to LAS/LAZ file
  LasReadTask(const std::string& path, bool shiftToOrigin = false);

  /// Copy constructor. (deleted)
  LasReadTask(const LasReadTask& other) = delete;

  /// Copy assignment operator. (deleted)
  LasReadTask& operator=(const LasReadTask& other) = delete;

  /// Destructor
  virtual ~LasReadTask() override; // Must be virtual for PIMPL pattern

  /// Check wheter file stream is ready.
  ///
  ///
  bool isReady() const;

  /// Open file input stream.
  ///
  /// This function may fail for various reasons: file doesn't
  /// exist, no permission to read, etc.
  ///
  /// \return True on success, false otherwise
  bool open();

  /// Check whether the file stream is open.
  ///
  /// \return True if open, false otherwise
  bool isOpen();

  /// Close the file input stream.
  void close();

  // Meta data from file header

  /// Get total point count, according to the file header.
  ///
  /// The file should be opened with open() before calling this function.
  /// Otherwise a default value (0) will be returned.
  ///
  /// \return Point count
  long long int pointCount() const;

  /// Indicator if the points have colors, according to the file header.
  ///
  /// The file should be opened with open() before calling this function.
  /// Otherwise a default value (0) will be returned.
  ///
  /// \return True if points have colors, false otherwise
  bool hasColors() const;

  /// Get spatial extent of all points, according to the file header.
  ///
  /// The file should be opened with open() before calling this function.
  /// Otherwise a default value (0) will be returned.
  ///
  /// \return Extent
  BoundingBox<double> extent() const;

protected:
  /// Perform read task
  void run() override;

private:
  class Impl;
  std::unique_ptr<LasReadTaskImpl> m_pimpl;
};

} // namespace io
} // namespace spatiumgl

#endif // SPATIUMGL_IO_LAS_LASREADTASK_H
