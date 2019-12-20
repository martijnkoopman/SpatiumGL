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

#ifndef SPATIUMGL_VECTOR_H
#define SPATIUMGL_VECTOR_H

#include "spatiumglexport.hpp"

#include <cstddef>          // std::size_t
#include <initializer_list> // std::initializer_list
#include <ostream>          // std::ostream

namespace spgl {
/// \class VectorBase
/// \brief Vector base class
///
/// Cannot be declared directly, only inherited.
template<typename T, size_t N>
struct SPATIUMGL_EXPORT VectorBase
{
public:
  /// Access element by reference.
  ///
  /// \param[in] index Index of element
  /// \return Element reference
  T& operator[](size_t index) { return m_data[index]; }

  /// Access element by const reference.
  ///
  /// \param[in] index Index of element
  /// \return Element const reference
  const T& operator[](size_t index) const { return m_data[index]; }

  /// Get number of elements in the vector.
  ///
  /// \return Number of elements.
  constexpr size_t size() const noexcept { return N; }

  /// Get pointer to data.
  ///
  /// \return Data pointer
  T* data() noexcept { return &m_data[0]; }

  /// Get const pointer to data.
  ///
  /// \return Const data pointer
  const T* data() const noexcept { return &m_data[0]; }

  /// Clear all values (set to 0).
  void clear()
  {
    // ERROR?: std::fill(std::begin(m_data), std::end(m_data), 0);
  }

protected:
  /// Default constructor
  VectorBase()
    : m_data{ 0 }
  {}

  //// Constructor
  // constexpr VectorBase(std::initializer_list<T> data)
  //	: m_data{ 0 }
  //{
  //	// Copy values
  //	size_t i = 0;
  //	auto it = data.begin();
  //	while(i < N && it != data.end())
  //	{
  //		m_data[i] = *it;

  //		++i;
  //		++it;
  //	}
  //}

  T m_data[N];
};

/// \class Vector
/// \brief Arbitrary fixed size vector
template<typename T, size_t N>
struct SPATIUMGL_EXPORT Vector : public VectorBase<T, N>
{
  /// Default constructor
  constexpr Vector() = default;

  /// Cast to vector with different element type (static_cast).
  ///
  /// \return Vector with cast element type
  template<typename T2>
  Vector<T2, N> staticCast() const
  {
    Vector<T2, N> result;

    for (size_t row = 0; row < N; row++) {
      result[row] = static_cast<T2>(this->m_data[row]);
    }

    return result;
  }

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other vector
  /// \return True if equal, otherwise false
  bool operator==(const Vector<T, N>& other) const
  {
    // Compare elements
    for (size_t i = 0; i < N; i++) {
      if (this->m_data[i] != other.m_data[i]) {
        return false;
      }
    }

    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other vector
  /// \return True if unequal, otherwise false
  bool operator!=(const Vector<T, N>& other) const
  {
    return !(operator==(other));
  }

  //// Arithmetic operators:

  ///// Add another vector.
  /////
  ///// \param[in] other Vector to add
  ///// \return Added vector
  // Vector<T, N> operator+(const Vector<T, N>& other) const
  //{
  //	VectorT<T, N> result;
  //	for (size_t row = 0; row < N; row++)
  //	{
  //		result[row] = operator[](row) + other[row];
  //	}
  //	return result;
  //}

  // ...
};
}

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace spgl {
/// Vector of 2 integer coordinates (x,y)
using Vector2i = Vector<int, 2>;

/// Vector of 2 double precision coordinates (x,y)
using Vector2 = Vector<double, 2>;

/// Vector of 2 single precision coordinates (x,y)
using Vector2f = Vector<float, 2>;

/// Vector of 3 double precision coordinates (x,y,z)
using Vector3 = Vector<double, 3>;

/// Vector of 3 single precision coordinates (x,y,z)
using Vector3f = Vector<float, 3>;

/// Vector of 4 double precision coordinates (x,y,z,w)
using Vector4 = Vector<double, 4>;
}

#endif // SPATIUMGL_VECTOR_H
