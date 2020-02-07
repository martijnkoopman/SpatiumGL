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

#ifndef SPATIUMGL_IO_LAS_LASPOINTSTATISTICS_H
#define SPATIUMGL_IO_LAS_LASPOINTSTATISTICS_H

#include "LasPoint.hpp"
#include "spatiumglexport.hpp"

#include <map>     // std::map
#include <ostream> // std::ostream

namespace spgl {
namespace io {

/// \class LasPointStatistics
/// \brief Statistics for LAS points
class SPATIUMGL_EXPORT LasPointStatistics
{
public:
  /// Constructor.
  ///
  /// \param[in] pointFormat LAS Point Data Format [0,10]
  LasPointStatistics(unsigned char pointFormat);

  /// Add LAS point.
  ///
  /// This will update the statistics.
  ///
  /// \param[in] lasPoint LAS point
  void addLasPoint(const LasPoint& lasPoint);

  /// Set LAS Point Data Format.
  ///
  /// \param[in] format LAS Point Data Format [0,10]
  void setPointFormat(unsigned char format) { m_pointFormat = format; }

  /// Get LAS Point Data Format. [0,10]
  ///
  /// \return LAS Point Data Format
  unsigned char pointFormat() const { return m_pointFormat; }

  /// Get point count.
  ///
  /// \return Point count
  long long pointCount() const { return m_pointCount; }

  /// Get minimum LAS point values.
  ///
  /// \return Minumum LAS point values.
  const LasPoint& min() const;

  /// Get maximum LAS point values.
  ///
  /// \return Minumum LAS point values.
  const LasPoint& max() const;

  /// Output to ostream
  friend std::ostream& operator<<(std::ostream& os,
                                  const LasPointStatistics& stats);

  /// Check for indication that GPS Time is present.
  ///
  /// \return True if GPS Time is present, false otherwise.
  bool hasGpsTime() const
  {
    return (m_min.gps_time != 0 || m_max.gps_time != 0);
  }

  /// Check for indication that RGB color is present.
  ///
  /// \return True if RGB color is present, false otherwise.
  bool hasRgb() const
  {
    return (m_min.rgb[0] != 0 || m_min.rgb[1] != 0 || m_min.rgb[2] != 0 ||
            m_max.rgb[0] != 0 || m_max.rgb[1] != 0 || m_max.rgb[2] != 0);
  }

  /// Check for indication that NIR is present.
  ///
  /// \return True if NIR is present, false otherwise.
  bool hasNir() const { return (m_min.nir != 0 || m_max.nir != 0); }

private:
  unsigned char m_pointFormat;
  long long m_pointCount;
  LasPoint m_min;
  LasPoint m_max;
  std::map<unsigned char, long> m_classifications;
  std::map<unsigned char, long> m_return_numbers;
};

} // namespace io
} // namespace spgl

#endif // SPATIUMGL_IO_LAS_LASPOINTSTATISTICS_H
