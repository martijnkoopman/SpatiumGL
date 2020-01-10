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

#ifndef SPATIUMGL_IO_LAS_LASREADER_H
#define SPATIUMGL_IO_LAS_LASREADER_H

#include "spatiumglexport.hpp"
#include "LasHeader.hpp"
#include "LasPoint.hpp"
#include "LasPointStatistics.hpp"

#include <memory> // std::unique_ptr

namespace spgl {
namespace io {

// Forward declare implementation
class LasReaderImpl;

/// \class LasReader
/// \brief Read points from LAS/LAZ file.
class SPATIUMGL_EXPORT LasReader
{
public:
  /// Constructor
  ///
  /// \param[in] path Path to LAS/LAZ file
  LasReader(const std::string& path);

  /// Copy constructor. (deleted)
  LasReader(const LasReader& other) = delete;

  /// Move constructor.
  LasReader(LasReader&& other) = default;

  /// Copy assignment operator. (deleted)
  LasReader& operator=(const LasReader& other) = delete;

  /// Move assignment operator.
  LasReader& operator=(LasReader&& other) = default;

  /// Destructor
  virtual ~LasReader(); // Must be virtual for PIMPL pattern

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
  bool isOpen();

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

  /// Read a single LAS point from file.
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
  const LasPoint& lasPoint() const;

private:
  // class Impl;
  std::unique_ptr<LasReaderImpl> m_pimpl;
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASREADER_H
