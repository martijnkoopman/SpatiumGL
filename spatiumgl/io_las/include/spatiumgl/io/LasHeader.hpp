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

#ifndef SPATIUMGL_IO_LAS_LASHEADER_H
#define SPATIUMGL_IO_LAS_LASHEADER_H

#include "spatiumglexport.hpp"
#include "spatiumgl/Bounds.hpp"
#include "spatiumgl/io/LasPointStatistics.hpp"

#include <array>

namespace spgl {
namespace io {

/// \class LasHeader
/// \brief LAS header
struct SPATIUMGL_EXPORT LasHeader
{
  unsigned char point_data_format = 0;
  long long number_of_point_records = 0;
  double scale_factor = 0;
  BoundingBox extent = {};
  bool compressed = false;

  /// Construct from LAS point statistics.
  ///
  /// The LAS Point Data Format is deduced from the present scalar fields.
  ///
  /// \param[in] pointStatistics Point statistics
  /// \return LAS header
  static LasHeader fromLasPointStatistics(
    const LasPointStatistics& pointStatistics)
  {
    LasHeader header;

    // Determine point data format
    const bool hasGpsTime = pointStatistics.hasGpsTime();
    const bool hasRgb = pointStatistics.hasRgb();
    const bool hasNir = pointStatistics.hasNir();
    if (hasNir) {
      header.point_data_format = 8;
    } else {
      if (hasGpsTime) {
        if (hasRgb) {
          header.point_data_format = 3;
        } else {
          header.point_data_format = 1;
        }
      } else {
        if (hasRgb) {
          header.point_data_format = 2;
        } else {
          header.point_data_format = 0;
        }
      }
    }

    header.number_of_point_records = pointStatistics.pointCount();
    header.scale_factor = 0;
    header.extent = BoundingBox::fromMinMax(pointStatistics.min().xyz,
                                            pointStatistics.max().xyz);
    header.compressed = false;

    return header;
  }
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASHEADER_H
