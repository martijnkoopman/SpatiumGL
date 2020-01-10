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

#include "spatiumglexport.hpp"
#include "spatiumgl/AsyncTask.hpp"
#include "spatiumgl/gfx3d/PointCloud.hpp"
#include "spatiumgl/io/LasReader.hpp"

#include <memory> // std::unique_ptr

namespace spgl {
namespace io {

// Forward declare implementation
class LasReadTaskImpl;

/// \class LasReadTask
/// \brief Read point cloud from LAS/LAZ file asynchronously.
class SPATIUMGL_EXPORT LasReadTask : public AsyncTask<gfx3d::PointCloud>
{
public:
  /// Constructor
  ///
  /// \param[in] path Path to LAS/LAZ file
  /// \param[in] readRgb If RGB color should be read
  /// \param[in] readScalars If scalars should to read
  LasReadTask(const std::string& path,
              bool readRgb = true,
              LasScalars readScalars = LasScalars::None);

  /// Copy constructor. (deleted)
  LasReadTask(const LasReadTask& other) = delete;

  /// Move constructor.
  LasReadTask(LasReadTask&& other) = default;

  /// Copy assignment operator. (deleted)
  LasReadTask& operator=(const LasReadTask& other) = delete;

  /// Move assignment operator.
  LasReadTask& operator=(LasReadTask&& other) = default;

  /// Destructor
  virtual ~LasReadTask() override = default;

  /// Validate file being read.
  ///
  /// \return Error message (empty if none)
  std::string validate();

  /// Get the LAS/LAZ reader.
  ///
  /// \return LAS/LAZ reader
  const LasReader& lasReader() const { return m_lasReader; }

protected:
  /// Perform read task
  void run() override;

private:
  LasReader m_lasReader;
  bool m_readRgb;
  LasScalars m_readScalars;
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASREADTASK_H
