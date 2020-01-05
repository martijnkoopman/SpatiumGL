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

#include "spatiumgl/io/LasHeader.hpp"
#include "spatiumgl/io/LasPoint.hpp"

#include "laswriter.hpp" // LASlib

#include <memory> // std::unique_ptr

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

  /// Copy constructor. (deleted)
  LasWriterImpl(const LasWriterImpl& other) = delete;

  /// Move constructor.
  LasWriterImpl(LasWriterImpl&& other) = default;

  /// Copy assignment operator. (deleted)
  LasWriterImpl& operator=(const LasWriterImpl& other) = delete;

  /// Move assignment operator.
  LasWriterImpl& operator=(LasWriterImpl&& other) = default;

  /// Destructor.
  ~LasWriterImpl();

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
  bool open(const LasHeader& header);

  /// Check whether the file stream is open.
  ///
  /// \return True if open, false otherwise
  bool isOpen() const;

  /// Close the file input stream.
  void close();

  // The following functions should only be called when file stream is open.

  /// Write a single LAS point to file.
  ///
  /// This function should only be called after the file is opened.
  ///
  /// \return True on success, false otherwise (end of file)
  /// \sa open
  void writeLasPoint(const LasPoint& point);

private:
  // LASlib
  LASwriteOpener m_lasWriteOpener;
  std::unique_ptr<LASwriter> m_lasWriter;
  LASheader m_lasHeader;
  LASpoint m_lasPoint;

  // SpatiumGL
  LasHeader m_header;
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASWRITERIMPL_H
