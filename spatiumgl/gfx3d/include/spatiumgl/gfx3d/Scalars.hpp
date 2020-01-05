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

#ifndef SPATIUMGL_GFX3D_SCALARS_H
#define SPATIUMGL_GFX3D_SCALARS_H

#include "spatiumglexport.hpp"

#include <vector>
#include <array>

namespace spgl {
namespace gfx3d {

/// \class Scalars
/// \brief Scalar values
template<typename T>
class Scalars
{
public:
  /// Constructor.
  ///
  /// \param[in] capacity Number of values to reserve in memory.
  /// \param[in] name Scalars name
  Scalars(size_t capacity = 0, std::string name = "")
    : m_name(name)
    , m_range()
    , m_values()
  {
    m_values.reserve(capacity);
  }

  /// Reserve memory.
  ///
  /// \param[in] capacity Number of values to reserve in memory.
  void reserve(size_t capacity)
  {
    m_values.reserve(capacity);
  }

  /// Add scalar value.
  ///
  /// This will automatically update the scalars range.
  ///
  /// \param[in] value Scalar value
  void addValue(T value)
  {
    if (m_values.size() == 0) {
      m_range[0] = m_range[1] = value;
    } else {
      m_range[0] = std::min(m_range[0], value);
      m_range[1] = std::max(m_range[1], value);
    }
  }

  /// Clear scalar values.
  ///
  /// This will free memory.
  void clear()
  {
    m_range = { 0, 0 };
    std::vector<T>().swap(m_values);
  }

  /// Get scalar values.
  ///
  /// \return Scalar values
  const std::vector<T>& values() const { return m_values; }

  /// Get scalars range (min, max)
  ///
  /// \return Scalars range
  const std::array<T, 2> range() const { return m_range; }

  /// Get scalars name.
  ///
  /// \return Scalars name
  const std::string& name() const { return m_name; }

private:
  std::string m_name;
  std::array<T, 2> m_range;
  std::vector<T> m_values;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_SCALARS_H
