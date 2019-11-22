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

#ifndef SPATIUMGL_VECTOR3_H
#define SPATIUMGL_VECTOR3_H

#include "Vector.hpp"

#include <cmath> // sqrt()

namespace spatiumgl {
/// \class Vector<T,3>
/// \brief Fixed size vector with length 3
template<typename T>
struct SPATIUMGL_EXPORT Vector<T, 3> : public VectorBase<T, 3>
{
  /// Default constructor
  constexpr Vector() = default;

  /// Constructor
  ///
  /// \param[in] x X value
  /// \param[in] y Y value
  /// \param[in] z Z value
  Vector(T x, T y, T z)
    : VectorBase<T, 3>()
  {
    this->m_data[0] = x;
    this->m_data[1] = y;
    this->m_data[2] = z;
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

  /// Cast to vector with different element type (static_cast).
  ///
  /// \return Vector with cast element type
  template<typename T2>
  Vector<T2, 3> staticCast() const
  {
    Vector<T2, 3> result;

    result[0] = static_cast<T2>(this->m_data[0]);
    result[1] = static_cast<T2>(this->m_data[1]);
    result[2] = static_cast<T2>(this->m_data[2]);

    return result;
  }

  // Compare operators

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other vector
  /// \return True if equal, otherwise false
  bool operator==(const Vector<T, 3>& other) const
  {
    if (this->m_data[0] != other.m_data[0] ||
        this->m_data[1] != other.m_data[1] ||
        this->m_data[2] != other.m_data[2]) {
      return false;
    }
    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other vector
  /// \return True if unequal, otherwise false
  bool operator!=(const Vector<T, 3>& other) const
  {
    return !(operator==(other));
  }

  // Arithmetic operators

  /// Add another vector.
  ///
  /// \param[in] other Vector to add
  /// \return Added vector
  Vector<T, 3> operator+(const Vector<T, 3>& other) const
  {
    Vector<T, 3> result;
    result[0] = this->m_data[0] + other[0];
    result[1] = this->m_data[1] + other[1];
    result[2] = this->m_data[2] + other[2];
    return result;
  }

  /// Subtract other vector.
  ///
  /// \param[in] other Vector to subtract
  /// \return Subtracted vector
  Vector<T, 3> operator-(const Vector<T, 3>& other) const
  {
    Vector<T, 3> result;
    result[0] = this->m_data[0] - other[0];
    result[1] = this->m_data[1] - other[1];
    result[2] = this->m_data[2] - other[2];
    return result;
  }

  /// Multiply by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Multiplied vector
  Vector<T, 3> operator*(T scalar) const
  {
    Vector<T, 3> result;
    result[0] = this->m_data[0] * scalar;
    result[1] = this->m_data[1] * scalar;
    result[2] = this->m_data[2] * scalar;
    return result;
  }

  /// Divide by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Divided vector
  Vector<T, 3> operator/(T scalar) const
  {
    Vector<T, 3> result;
    result[0] = this->m_data[0] / scalar;
    result[1] = this->m_data[1] / scalar;
    result[2] = this->m_data[2] / scalar;
    return result;
  }

  /// Calculate length of vector (magnitude, euclidean).
  ///
  /// \return Length
  constexpr T length() const
  {
    return sqrt(this->m_data[0] * this->m_data[0] +
                this->m_data[1] * this->m_data[1] +
                this->m_data[2] * this->m_data[2]);
  }

  /// Normalize the vector.
  /// A normalized vector has length = 1.
  void normalize()
  {
    const T l = length();
    this->m_data[0] = this->m_data[0] / l;
    this->m_data[1] = this->m_data[1] / l;
    this->m_data[2] = this->m_data[2] / l;
  }

  /// Get normalized copy of vector.
  /// A normalized vector has length = 1.
  ///
  /// \return Normalized vector
  Vector<T, 3> normalized() const
  {
    const T l = length();
    Vector<T, 3> result;
    result[0] = this->m_data[0] / l;
    result[1] = this->m_data[1] / l;
    result[2] = this->m_data[2] / l;
    return result;
  }

  // Geometric operations

  /// Calculate dot product with vector.
  /// Dot product = 0: vectors are orthogonal (perpendicular).
  /// Dot product = |a||b| (1 if normalized): vectors are parallel.
  ///
  /// \param[in] other Other vector
  /// \return Dot product
  constexpr T dot(const Vector<T, 3>& other) const
  {
    return (this->m_data[0] * other[0] + this->m_data[1] * other[1] +
            this->m_data[2] * other[2]);
  }

  /// Calculate cross product with vector.
  /// The cross product is perpendicular to the two input vectors.
  /// The result can be NaN.
  ///
  /// \param[in] other Other vector
  /// \return Cross product
  Vector<T, 3> cross(const Vector<T, 3>& other) const
  {
    Vector<T, 3> result;
    result.x() = y() * other.z() - z() * other.y();
    result.y() = z() * other.x() - x() * other.z();
    result.z() = x() * other.y() - y() * other.x();
    return result;
  }

  /// Calculate angle with vector.
  ///
  /// \param[in] other Other vector
  /// \return Angle in radians
  constexpr T angle(const Vector<T, 3>& other) const
  {
    return acos((this->dot(other)) / (this->length() * other.length()));
  }

  /// Project vector onto vector.
  ///
  /// \param[in] other Vector to project
  /// \return Projected vector
  Vector<T, 3> project(const Vector<T, 3>& other) const
  {
    return this->normalized() * (other.dot(*this) / this->length());
  }

  /// Output to ostream
  friend std::ostream& operator<<(std::ostream& os, const Vector<T, 3>& vector)
  {
    os << "(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ")";
    return os;
  }
};
}

#endif // SPATIUMGL_VECTOR3_H