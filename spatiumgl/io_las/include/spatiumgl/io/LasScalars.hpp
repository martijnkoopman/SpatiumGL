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

#ifndef SPATIUMGL_IO_LAS_LASSCALARS_H
#define SPATIUMGL_IO_LAS_LASSCALARS_H

#include "spatiumglexport.hpp"

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

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASSCALARS_H
