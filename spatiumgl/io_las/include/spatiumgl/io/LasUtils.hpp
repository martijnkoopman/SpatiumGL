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

#ifndef SPATIUMGL_IO_LAS_LASUTILS_H
#define SPATIUMGL_IO_LAS_LASUTILS_H

#include "spatiumglexport.hpp"

#include <set>
#include <string>

namespace spgl {
namespace io {

/// \class LasUtils
/// \brief LAS utility functions
class SPATIUMGL_EXPORT LasUtils
{
public:
  LasUtils() = delete;

  /// Check if RGB fields are present according to LAS Point Data Format.
  ///
  /// \param[in] format Point data format
  /// \return True if present, false otherwise
  static bool formatHasRgb(unsigned char format)
  {
    return (std::set<unsigned char>{ 2, 3, 5, 7, 8, 10 }.count(format) > 0);
  }

  /// Check if GPS Time field is present according to LAS Point Data Format.
  ///
  /// \param[in] format Point data format
  /// \return True if present, false otherwise
  static bool formatHasGpsTime(unsigned char format)
  {
    return (
      std::set<unsigned char>{ 1, 3, 4, 5, 6, 7, 8, 9, 10 }.count(format) > 0);
  }

  /// Check if NIR field is present according to LAS Point Data Format.
  ///
  /// \param[in] format Point data format
  /// \return True if present, false otherwise
  static bool formatHasNir(unsigned char format) { return (format == 8); }

  /// Calculate LAS Point Data Record Length based on LAS Point Data Format.
  ///
  /// \param[in] format Point data format
  /// \return LAS Point Data Record Length
  static unsigned short formatRecordSize(unsigned char format)
  {
    switch (format) {
      case 0:
        return 20;
      case 1:
        // GPS Time
        return 28;
      case 2:
        // RGB
        return 26;
      case 3:
        // RGB + GPS Time
        return 34;
      case 4:
        // GPS Time + Wave packets
        return 57;
      case 5:
        // RGB + GPS Time + Wave Packets
        return 63;
      case 6:
        // More bits for return numbers, classifications and scan angle.
        // + GPS time
        return 30;
      case 7:
        // 6 + RGB
        return 36;
      case 8:
        // 6 + RGB + NIR
        return 38;
      case 9:
        // 6 + Wave Packets
        return 59;
      case 10:
        // 6 +  RGB + NIR + Wave Packets
        return 67;
      default:
        return 0;
    }
  }

  /// Convert point classification to string.
  ///
  /// \param[in] classification Point classification (0 - 255)
  /// \param[in] format Point data format (0 - 10)
  /// \return Classification name
  static std::string
  classificationToString(unsigned char classification,
                         unsigned char point_data_format)
  {
    if (point_data_format < 6) {
      switch (classification) {
        case 0:
          return "Never classified";
        case 1:
          return "Unclassified";
        case 2:
          return "Ground";
        case 3:
          return "Low Vegetation";
        case 4:
          return "Medium Vegetation";
        case 5:
          return "High Vegetation";
        case 6:
          return "Building";
        case 7:
          return "Low Point (noise)";
        case 8:
          return "Model Key-point (mass point)";
        case 9:
          return "Water";
        case 12:
          return "Overlap Points";
        case 10:
        case 11:
        default:
          return "Reserved";
      }
    } else {
      switch (classification) {
        case 0:
          return "Never classified";
        case 1:
          return "Unclassified";
        case 2:
          return "Ground";
        case 3:
          return "Low Vegetation";
        case 4:
          return "Medium Vegetation";
        case 5:
          return "High Vegetation";
        case 6:
          return "Building";
        case 7:
          return "Low Point (noise)";
        case 8:
          return "Model Key-point (mass point)";
        case 9:
          return "Water";
        case 10:
          return "Rail";
        case 11:
          return "Road Surface";
        case 12:
          return "Reserved";
        case 13:
          return "Wire - Guard (Shield)";
        case 14:
          return "Wire - Conductor (Phase)";
        case 15:
          return "Transmission Tower";
        case 16:
          return "Wire-structure Connector";
        case 17:
          return "Bridge Deck";
        case 18:
          return "High Noise";
      }
      if (classification > 17 && classification < 64) {
        return "Reserved";
      } else {
        return "User defined";
      }
    }
  }
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASUTILS_H
