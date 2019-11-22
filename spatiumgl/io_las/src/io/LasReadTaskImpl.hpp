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

#ifndef SPATIUMGL_IO_LAS_LASREADTASKIMPL_H
#define SPATIUMGL_IO_LAS_LASREADTASKIMPL_H

#include "spatiumgl/gfx3d/PointCloud.hpp"

#include "lasreader.hpp" // LASlib

#include <memory> // std::unique_ptr

namespace spatiumgl {
namespace io {

/// \class LasReadTaskImpl
/// \brief LASlib implementation to read point cloud from LAS/LAZ file.
class LasReadTaskImpl
{
public:
  /// Constructor.
  ///
  /// \param[in] path Path to LAS/LAZ file
  /// \param[in] shiftToOrigin Perform shift of point positions to origin.
  LasReadTaskImpl(const std::string& path, const bool shiftToOrigin);

  /// Copy constructor. (deleted)
  LasReadTaskImpl(const LasReadTaskImpl& other) = delete;

  /// Move constructor.
  LasReadTaskImpl(LasReadTaskImpl&& other) = default;

  /// Copy assignment operator. (deleted)
  LasReadTaskImpl& operator=(const LasReadTaskImpl& other) = delete;

  /// Move assignment operator.
  LasReadTaskImpl& operator=(LasReadTaskImpl&& other) = default;

  /// Destructor.
  ~LasReadTaskImpl();

  std::string path() const;

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
  bool isOpen() const;

  /// Close the file input stream.
  void close();

  /// Read a single point from file.
  ///
  /// \return True on success, false otherwise (end of file)
  bool readPoint();

  /// Get position of last read point.
  ///
  /// \return Point position
  /// \sa readPoint
  Vector3 lastReadPointPosition();

  /// Get color of last read point.
  ///
  /// \return Point color
  /// \sa readPoint
  Vector3 lastReadPointColor();

  /// Get total point count, according to the file header.
  ///
  /// \return Point count
  long long int pointCount() const;

  /// Indicator if the points have colors, according to the file header.
  ///
  /// \return True if points have colors, false otherwise
  bool hasColors() const;

  /// Get spatial extent of all points, according to the file header.
  ///
  /// \return Extent
  BoundingBox<double> extent() const;

  /// Get indicator if shift to origin should be applied on all points.
  ///
  /// \return True is shift applied, false otherwise.
  bool shiftToOrigin() const { return m_shiftToOrigin; }

  /// Get spatial origin shift.
  ///
  /// \return origin shift
  Vector3 originShift() const;

private:
  LASreadOpener m_lasreadopener;
  std::unique_ptr<LASreader> m_reader;
  bool m_shiftToOrigin;
};

} // namespace io
} // namespace spatiumgl

#endif // SPATIUMGL_IO_LAS_LASREADTASKIMPL_H
