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

#include "spatiumgl/io/LasHeader.hpp"
#include "spatiumgl/io/LasPoint.hpp"
#include "spatiumgl/io/LasPointStatistics.hpp"

#include "lasreader.hpp" // LASlib

#include <memory> // std::unique_ptr

namespace spgl {
namespace io {

/// \class LasReadTaskImpl
/// \brief LASlib implementation to read point cloud from LAS/LAZ file.
class LasReaderImpl
{
public:
  /// Constructor.
  ///
  /// \param[in] path Path to LAS/LAZ file
  LasReaderImpl(const std::string& path);

  /// Copy constructor. (deleted)
  LasReaderImpl(const LasReaderImpl& other) = delete;

  /// Move constructor.
  LasReaderImpl(LasReaderImpl&& other) = default;

  /// Copy assignment operator. (deleted)
  LasReaderImpl& operator=(const LasReaderImpl& other) = delete;

  /// Move assignment operator.
  LasReaderImpl& operator=(LasReaderImpl&& other) = default;

  /// Destructor.
  ~LasReaderImpl();

  /// Get LAS/LAZ file path.
  ///
  /// \return LAS/LAZ file path.
  std::string path() const;

  /// Check wheter file stream is ready for reading.
  ///
  /// \return True if ready, false otherwise.
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

  // The following functions should only be called when file stream is open.

  /// Get LAS/LAZ file header.
  ///
  /// This function should only be called after the file is opened.
  ///
  /// \return LAS/LAZ file header
  /// \sa open()
  const LasHeader& lasHeader() const;

  /// Get LAS point statistics.
  ///
  /// These statistics are upated every time a new point is read from file.
  ///
  /// This function should only be called after the file is opened and at
  /// least one point is read.
  ///
  /// \return LAS point statistics
  /// \sa open
  /// \sa readLasPoint
  const LasPointStatistics& lasPointStatistics() const;

  /// Read a single point from file.
  ///
  /// This function should only be called after the file is opened.
  ///
  /// \return True on success, false otherwise (end of file)
  /// \sa open
  bool readLasPoint();

  /// Get last read LAS point.
  ///
  /// This function should only be called after the file is opened and a point
  /// is read.
  ///
  /// \return Last read LAS point
  /// \sa open
  /// \sa readLasPoint
  const LasPoint &lasPoint() const;

private:
  // LASlib
  LASreadOpener m_lasReadOpener;
  std::unique_ptr<LASreader> m_lasReader;

  // SpatiumGL
  LasHeader m_header;
  LasPointStatistics m_pointStatistics;
  LasPoint m_point;
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASREADERIMPL_H
