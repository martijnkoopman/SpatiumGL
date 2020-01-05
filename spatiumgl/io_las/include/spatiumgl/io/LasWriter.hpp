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

#include "spatiumglexport.hpp"
#include "LasHeader.hpp"
#include "LasPoint.hpp"

#include <memory> // std::unique_ptr

namespace spgl {
namespace io {

// Forward declare implementation
class LasWriterImpl;

/// \class LasWriter
/// \brief Write points to LAS/LAZ file.
class SPATIUMGL_EXPORT LasWriter
{
public:
  /// Constructor
  ///
  /// \param[in] path Path to LAS/LAZ file
  LasWriter(const std::string& path = "");

  /// Copy constructor. (deleted)
  LasWriter(const LasWriter& other) = delete;

  /// Move constructor.
  LasWriter(LasWriter&& other) = default;

  /// Copy assignment operator. (deleted)
  LasWriter& operator=(const LasWriter& other) = delete;

  /// Move assignment operator.
  LasWriter& operator=(LasWriter&& other) = default;

  /// Destructor
  virtual ~LasWriter(); // Must be virtual for PIMPL pattern

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
  /// \param[in] lasHeader LAS header
  /// \return True on success, false otherwise
  bool open(const LasHeader& lasHeader);

  /// Check whether the file stream is open.
  ///
  /// \return True if open, false otherwise
  bool isOpen();

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
  std::unique_ptr<LasWriterImpl> m_pimpl;
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASWRITER_H
