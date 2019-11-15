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

#ifndef SPATIUMGL_VECTOR4_H
#define SPATIUMGL_VECTOR4_H

#include "Vector.hpp"

namespace spatiumgl {
/// \class Vector<T,4>
/// \brief Fixed size vector with length 4
template<typename T>
struct SPATIUMGL_EXPORT Vector<T, 4> : public VectorBase<T, 4>
{
  /// Default constructor
  Vector() = default;

  /// Constructor
  ///
  /// \param[in] x X value
  /// \param[in] y Y value
  /// \param[in] z Z value
  /// \param[in] w W value
  Vector(T x, T y, T z, T w)
    : VectorBase<T, 4>()
  {
    this->m_data[0] = x;
    this->m_data[1] = y;
    this->m_data[2] = z;
    this->m_data[3] = w;
  }

  Vector(const Vector<T, 3>& xyz, T w)
    : VectorBase<T, 4>()
  {
    this->m_data[0] = xyz[0];
    this->m_data[1] = xyz[1];
    this->m_data[2] = xyz[2];
    this->m_data[3] = w;
  }

  /// Access X element by reference.
  ///
  /// \return X element reference
  T& x() { return this->m_data[0]; }

  /// Access X element by const reference.
  ///
  /// \return X element const reference
  const T& x() const { return this->m_data[0]; }

  /// Access Y element by reference.
  ///
  /// \return Y element reference
  T& y() { return this->m_data[1]; }

  /// Access Y element by const reference.
  ///
  /// \return Y element const reference
  const T& y() const { return this->m_data[1]; }

  /// Access Z element by reference.
  ///
  /// \return Z element reference
  T& z() { return this->m_data[2]; }

  /// Access Z element by const reference.
  ///
  /// \return Z element const reference
  const T& z() const { return this->m_data[2]; }

  /// Access W element by reference.
  ///
  /// \return W element reference
  T& w() { return this->m_data[3]; }

  /// Access W element by const reference.
  ///
  /// \return W element const reference
  const T& w() const { return this->m_data[3]; }

  /// Cast to vector with different element type (static_cast).
  ///
  /// \return Vector with cast element type
  template<typename T2>
  Vector<T2, 4> staticCast() const
  {
    Vector<T2, 4> result;

    result[0] = static_cast<T2>(this->m_data[0]);
    result[1] = static_cast<T2>(this->m_data[1]);
    result[2] = static_cast<T2>(this->m_data[2]);
    result[3] = static_cast<T2>(this->m_data[3]);

    return result;
  }

  // Compare operators

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other vector
  /// \return True if equal, otherwise false
  bool operator==(const Vector<T, 4>& other) const
  {
    if (this->m_data[0] != other.m_data[0] ||
        this->m_data[1] != other.m_data[1] ||
        this->m_data[2] != other.m_data[2] ||
        this->m_data[3] != other.m_data[3]) {
      return false;
    }
    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other vector
  /// \return True if unequal, otherwise false
  bool operator!=(const Vector<T, 4>& other) const
  {
    return !(operator==(other));
  }

  // Arithmetic operators

  /// Add another vector.
  ///
  /// \param[in] other Vector to add
  /// \return Added vector
  Vector<T, 4> operator+(const Vector<T, 4>& other) const
  {
    Vector<T, 4> result;
    result[0] = this->m_data[0] + other[0];
    result[1] = this->m_data[1] + other[1];
    result[2] = this->m_data[2] + other[2];
    result[3] = this->m_data[3] + other[3];
    return result;
  }

  /// Subtract other vector.
  ///
  /// \param[in] other Vector to subtract
  /// \return Subtracted vector
  Vector<T, 4> operator-(const Vector<T, 4>& other) const
  {
    Vector<T, 4> result;
    result[0] = this->m_data[0] - other[0];
    result[1] = this->m_data[1] - other[1];
    result[2] = this->m_data[2] - other[2];
    result[3] = this->m_data[3] - other[3];
    return result;
  }

  /// Multiply by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Multiplied vector
  Vector<T, 4> operator*(T scalar) const
  {
    Vector<T, 4> result;
    result[0] = this->m_data[0] * scalar;
    result[1] = this->m_data[1] * scalar;
    result[2] = this->m_data[2] * scalar;
    result[3] = this->m_data[3] * scalar;
    return result;
  }

  /// Divide by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Divided vector
  Vector<T, 4> operator/(T scalar) const
  {
    Vector<T, 4> result;
    result[0] = this->m_data[0] / scalar;
    result[1] = this->m_data[1] / scalar;
    result[2] = this->m_data[2] / scalar;
    result[3] = this->m_data[3] / scalar;
    return result;
  }

  /// Calculate length of vector (magnitude, euclidean).
  ///
  /// \return Length
  constexpr T length() const
  {
    return sqrt(
      this->m_data[0] * this->m_data[0] + this->m_data[1] * this->m_data[1] +
      this->m_data[2] * this->m_data[2] + this->m_data[3] * this->m_data[3]);
  }

  /// Normalize the vector.
  /// A normalized vector has length = 1.
  void normalize()
  {
    const T l = length();
    this->m_data[0] = this->m_data[0] / l;
    this->m_data[1] = this->m_data[1] / l;
    this->m_data[2] = this->m_data[2] / l;
    this->m_data[3] = this->m_data[3] / l;
  }

  /// Get normalized copy of vector.
  /// A normalized vector has length = 1.
  ///
  /// \return Normalized vector
  Vector<T, 4> normalized() const
  {
    const T l = length();
    Vector<T, 4> result;
    result[0] = this->m_data[0] / l;
    result[1] = this->m_data[1] / l;
    result[2] = this->m_data[2] / l;
    result[3] = this->m_data[3] / l;
    return result;
  }
};
}

#endif // SPATIUMGL_VECTOR4_H
