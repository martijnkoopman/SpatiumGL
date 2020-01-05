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

#include <array>            // std::array
#include <cstddef>          // std::size_t
#include <cmath>            // std::sqrt
#include <ostream>          // std::ostream

namespace spgl {

template<bool cond, typename U>
using spgl_enable_if_t  = typename std::enable_if<cond, U>::type;

template<typename T,
         size_t N, spgl_enable_if_t<std::is_arithmetic<T>::value, int> = 0>
struct SPATIUMGL_EXPORT Vector
{
/// \todo Enforce N >= 1
public:
  /// Default constructor.
  ///
  /// Initializes all elements to 0.
  Vector()
    : m_data{ 0 }
  {}

  /// Constructor.
  ///
  /// \param[in] value Value for all elements
  Vector(T value)
    : m_data{ 0 }
  {
    for(size_t i = 0; i < N; i++) {
      m_data[i] = value;
    }
  }

  /// Constructor.
  ///
  /// \param[in] other Other vector
  /// \param[in] value Value of last element
  Vector(const Vector<T, N - 1>& other, T value)
    : m_data{ 0 }
  {
    for (size_t i = 0; i < N - 1; i++) {
      m_data[i] = other[i];
    }
    m_data[N - 1] = value;
  }

  /// Constructor.
  ///
  /// \param[in] values Element values
  template<typename... Args,
           typename std::enable_if<N == sizeof...(Args), int>::type = 0>
  Vector(Args... values)
    : m_data{ std::forward<Args>(values)... }
  {
    /// \todo Enforce variadic arguments are of type T or static_cast
  }

  /// Cast to vector with different element type.
  ///
  /// \return Vector with casted element type
  template<typename T2>
  Vector<T2, N> staticCast() const
  {
    Vector<T2, N> result;
    for (size_t i = 0; i < N; i++) {
      result[i] = static_cast<T2>(m_data[i]);
    }
    return result;
  }

  // Compare operators

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other vector
  /// \return True if equal, false otherwise
  bool operator==(const Vector<T, N>& other) const
  {
    for (size_t row = 0; row < N; row++) {
      if (m_data[row] != other[row]) {
        return false;
      }
    }
    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other vector
  /// \return True if unequal, false otherwise
  bool operator!=(const Vector<T, N>& other) const
  {
    return !(operator==(other));
  }

  // Data access

  /// Access element.
  ///
  /// \param[in] index Index of element
  /// \return Element
  T& operator[](size_t index) { return m_data[index]; }

  /// Access element.
  ///
  /// \param[in] index Index of element
  /// \return Element
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

  /// Access X element by reference.
  ///
  /// \return X element reference
  template<typename U = T&>
  spgl_enable_if_t<N >= 1, U> x()
  {
    return this->m_data[0];
  }

  /// Access X element by const reference.
  ///
  /// \return X element const reference
  template<typename U = const T&>
  spgl_enable_if_t<N >= 1, U> x() const
  {
    return this->m_data[0];
  }

  /// Access Y element by reference.
  ///
  /// \return Y element reference
  template<typename U = T&>
  spgl_enable_if_t<N >= 2, U> y()
  {
    return this->m_data[1];
  }

  /// Access Y element by const reference.
  ///
  /// \return Y element const reference
  template<typename U = const T&>
  spgl_enable_if_t<N >= 2, U> y() const
  {
    return this->m_data[1];
  }

  /// Access Z element by reference.
  ///
  /// \return Z element reference
  template<typename U = T&>
  spgl_enable_if_t<N >= 3, U> z()
  {
    return this->m_data[2];
  }

  /// Access Z element by const reference.
  ///
  /// \return Z element const reference
  template<typename U = const T&>
  spgl_enable_if_t<N >= 3, U> z() const
  {
    return this->m_data[2];
  }

  /// Access W element by reference.
  ///
  /// \return W element reference
  template<typename U = T&>
  spgl_enable_if_t<N >= 4, U> w()
  {
    return this->m_data[3];
  }

  /// Access W element by const reference.
  ///
  /// \return W element const reference
  template<typename U = const T&>
  spgl_enable_if_t<N >= 4, U> w() const
  {
    return this->m_data[3];
  }

  // Arithmetic operators:

  /// Add another vector.
  ///
  /// \param[in] other Vector to add
  /// \return Added vector
   Vector<T, N> operator+(const Vector<T, N>& other) const
  {
    Vector<T, N> result;
    for (size_t row = 0; row < N; row++)
    {
      result[row] = m_data[row] + other[row];
    }
    return result;
  }

  /// Subtract other vector.
  ///
  /// \param[in] other Vector to subtract
  /// \return Subtracted vector
  Vector<T, N> operator-(const Vector<T, N>& other) const
  {
    Vector<T, N> result;
    for (size_t row = 0; row < N; row++) {
      result[row] = m_data[row] - other[row];
    }
    return result;
  }

  /// Multiply by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Multiplied vector
  Vector<T, N> operator*(T scalar) const
  {
    Vector<T, N> result;
    for (size_t row = 0; row < N; row++) {
      result[row] = m_data[row] * scalar;
    }
    return result;
  }

  /// Divide by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Divided vector
  Vector<T, N> operator/(T scalar) const
  {
    Vector<T, N> result;
    for (size_t row = 0; row < N; row++) {
      result[row] = m_data[row] / scalar;
    }
    return result;
  }

  /// Calculate magnitude of vector (length, euclidean).
  ///
  /// \return Magnitude
  T magnitude() const
  {
    T result = 0;
    for (size_t row = 0; row < N; row++) {
      result += m_data[row] * m_data[row];
    }
    return std::sqrt(result);
  }

  /// Normalize the vector.
  /// A normalized vector has length = 1.
  void normalize()
  {
    const T l = magnitude();
    for (size_t row = 0; row < N; row++) {
      m_data[row] /= l;
    }
  }

  /// Get normalized copy of vector.
  /// A normalized vector has length = 1.
  ///
  /// \return Normalized vector
  Vector<T, N> normalized() const
  {
    const T l = magnitude();
    Vector<T, N> result;
    for (size_t row = 0; row < N; row++) {
      result[row] = m_data[row] / l;
    }
    return result;
  }

  // Geometric operations

  /// Calculate dot product with vector.
  /// Dot product = 0: vectors are orthogonal (perpendicular).
  /// Dot product = |a||b| (1 if normalized): vectors are parallel.
  ///
  /// \param[in] other Other vector
  /// \return Dot product
  template<typename U = T>
  spgl_enable_if_t<N >= 2, U> dot(const Vector<T, N>& other) const
  {
    T result = 0;
    for (size_t row = 0; row < N; row++) {
      result += m_data[row] * other[row];
    }
    return result;
  }

  /// Calculate cross product with vector.
  /// The cross product is perpendicular to the two input vectors.
  /// The result can be NaN.
  ///
  /// \param[in] other Other vector
  /// \return Cross product
  template<typename U = Vector<T, 3>>
  spgl_enable_if_t<N == 3, U> cross(const Vector<T, 3>& other) const
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
  template<typename U = T>
  spgl_enable_if_t<N >= 2, U> angle(const Vector<T, N>& other) const
  {
    return acos((this->dot(other)) / (this->magnitude() * other.magnitude()));
  }

  /// Project vector onto vector.
  ///
  /// \param[in] other Vector to project
  /// \return Projected vector
  template<typename U = Vector<T, N>>
  spgl_enable_if_t<N >= 2, U> project(const Vector<T, N>& other) const
  {
    return this->normalized() * (other.dot(*this) / this->magnitude());
  }

  /// Calculate distance to other vector. (euclidean)
  ///
  /// \param[in] other Other vector.
  /// \return Euclidean distance
  template<typename U = T>
  spgl_enable_if_t<N >= 2, U> distance(const Vector<T, N>& other) const
  {
    T result = 0;
    for (size_t row = 0; row < N; row++) {
      result += (m_data[row] - other[row]) * (m_data[row] - other[row]);
    }
    return std::sqrt(result);
  }

  /// Output to ostream
  friend std::ostream& operator<<(std::ostream& os,
                                  const Vector<T, N>& vector)
  {
    os << "(";
    if (N > 0) {
      size_t row;
      for (row = 0; row < N - 1; row++) {
        os << vector[row] << ", ";
      }
      os << vector[row];
    }
    os << ")";
    return os;
  }

private:
  std::array<T, N> m_data;
};

/// Vector of 2 double precision coordinates (x,y)
using Vector2 = Vector<double, 2>;

/// Vector of 2 single precision coordinates (x,y)
using Vector2f = Vector<float, 2>;

/// Vector of 2 integer coordinates (x,y)
using Vector2i = Vector<int, 2>;

/// Vector of 3 double precision coordinates (x,y,z)
using Vector3 = Vector<double, 3>;

/// Vector of 3 single precision coordinates (x,y,z)
using Vector3f = Vector<float, 3>;

/// Vector of 3 integer coordinates (x,y,z)
using Vector3i = Vector<int, 3>;

/// Vector of 4 double precision coordinates (x,y,z,w)
using Vector4 = Vector<double, 4>;

/// Vector of 4 single precision coordinates (x,y,z,w)
using Vector4f = Vector<float, 4>;

/// Vector of 4 integer coordinates (x,y,z,w)
using Vector4i = Vector<int, 4>;

} // namespace spgl

























/*










/// \class VectorBase
/// \brief Vector base class
///
/// Cannot be declared directly, only inherited.
// , typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
template<typename T, size_t N>
struct SPATIUMGL_EXPORT VectorBase
{
public:
  /// Access element.
  ///
  /// \param[in] index Index of element
  /// \return Element reference
  T& operator[](size_t index) { return m_data[index]; }

  /// Access element.
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

  /// Constructor.
  ///
  /// \param[in] data Data array
  VectorBase(const std::array<T,N> &data)
    : m_data(data)
  {}

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

  std::array<T,N> m_data;
};

/// \class Vector
/// \brief Arbitrary fixed size vector
template<typename T, size_t N>
struct SPATIUMGL_EXPORT Vector : public VectorBase<T, N>
{
  /// Default constructor
  constexpr Vector() = default;

  /// Constructor.
  ///
  /// \param[in] data Data array
  Vector(const std::array<T, N>& data)
    : VectorBase<T,N>(data)
  {}

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

  // Compare operators

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

/// Vector of 3 integer coordinates (x,y,z)
using Vector3i = Vector<int, 3>;

/// Vector of 4 double precision coordinates (x,y,z,w)
using Vector4 = Vector<double, 4>;
}

*/

#endif // SPATIUMGL_VECTOR_H
