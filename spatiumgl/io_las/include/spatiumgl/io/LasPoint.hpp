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

#ifndef SPATIUMGL_IO_LAS_LASPOINT_H
#define SPATIUMGL_IO_LAS_LASPOINT_H

#include "spatiumglexport.hpp"
#include "spatiumgl/Vector.hpp"

#include <array>

namespace spgl {
namespace io {

enum SPATIUMGL_EXPORT LasScalars : int
{
  None,
  Intensity,
  ReturnNumber,
  NumberOfReturns,
  Classification,
  ScanAngleRank,
  UserData,
  PointSourceId,
  GpsTime,
  Nir
};

/// \class LasPoint
/// \brief LAS point for APRS LAS 1.0 - 1.3 (extended 1.4 not supported)
struct SPATIUMGL_EXPORT LasPoint
{
  Vector3 xyz = {};
  unsigned short intensity = 0;
  unsigned char return_number = 0;
  unsigned char number_of_returns = 0;
  unsigned char classification = 0;
  char scan_angle_rank = 0;
  unsigned char user_data = 0;
  unsigned short point_source_ID = 0;
  double gps_time = 0;
  std::array<unsigned short, 3> rgb = { 0 };
  unsigned short nir = 0;

  float scalarValue(LasScalars scalar) const
  {
    switch (scalar) {
      case Intensity:
        // Range: 0 - 65535
        return static_cast<float>(intensity);
      case ReturnNumber:
        // Range: 0  - 255
        return static_cast<float>(return_number);
      case NumberOfReturns:
        // Range: 0  - 255
        return static_cast<float>(number_of_returns);
      case Classification:
        // Range: 0  - 255
        return static_cast<float>(classification);
      case ScanAngleRank:
        // Range: -90 + 90
        return static_cast<float>(scan_angle_rank);
      case UserData:
        // Range: 0  - 255
        return static_cast<float>(user_data);
      case PointSourceId:
        // Range: 0 - 65535
        return static_cast<float>(point_source_ID);
      case GpsTime:
        // Range: -MIN_FLOAT_VAL - +MAX_FLOAT_VAL
        return static_cast<float>(gps_time);
      case Nir:
        // Range: 0 - 65535
        return static_cast<float>(nir);
      default:
        return 0;
    }
  }
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASPOINT_H
