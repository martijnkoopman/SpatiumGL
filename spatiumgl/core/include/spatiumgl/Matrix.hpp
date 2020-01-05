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

#ifndef SPATIUMGL_MATRIX_H
#define SPATIUMGL_MATRIX_H

#include "Vector.hpp"
#include "spatiumglexport.hpp"

#include <ostream>

#ifdef __linux__
#undef minor
#endif

namespace spgl {

/// \class Matrix
///
/// Internally a matrix is stored as an array of column vectors.
///
/// Example layout:
/// | 00 04 08 12 |
/// | 01 05 09 13 |
/// | 02 06 10 14 |
/// | 03 07 11 15 |
///
///  Memory layout:
/// [00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15]
///
/// Element access:
/// matrix[col][row] returns a reference or const reference (if matrix is
/// const).
///
/// Fast iteration over a matrix:
/// Matrix<T,W,H> matrix;
/// for (size_t col = 0; col < W; col++)
/// {
///   Vector<T,H> &column = matrix[col]; // reference to column vector
///	  for (size_t row = 0; row < H; row++)
///   {
///     T& val = column[row]; // reference to element
///     // Do something with val...
///   }
/// }
template<typename T,
         size_t W,
         size_t H,
         spgl_enable_if_t<std::is_arithmetic<T>::value, int> = 0>
struct SPATIUMGL_EXPORT Matrix
{
  /// \todo Enforce W,H >= 1
public:
  /// Default constructor.
  ///
  /// Initializes all elements to 0.
  Matrix()
    : m_columns()
  {}

  /// Constructor.
  ///
  /// \param[in] diagonal Value for all diagonal elements
  template<typename U = T, typename std::enable_if<W == H, U>::type = 0>
  Matrix(U value)
    : m_columns()
  {
    for (size_t i = 0; i < W; i++) {
      m_columns[i][i] = value;
    }
  }

  /// Constructor.
  ///
  /// Example:
  /// Matrix<double, 2, 3> = { 1, 2, 3, 4, 5, 6 };
  ///
  /// \param[in] values Element values in column-major order.
  template<typename... Args,
           typename std::enable_if<W * H == sizeof...(Args), int>::type = 0>
  Matrix(Args... values)
    : m_columns()
  {
    size_t i = 0;
    for (auto&& x : { values... }) {
      const size_t col = i / W;
      const size_t row = i % H;
      m_columns[col][row] = x;
      i++;
    }
  }

  /// Constructor.
  ///
  /// Example:
  /// Matrix<double, 2, 3> = { {1, 2, 3}, {4, 5, 6} };
  ///
  /// \param[in] values Element values in column-major order.
  Matrix(const std::initializer_list<std::initializer_list<T>>& values)
    : m_columns()
  {
    auto colIt = values.begin();
    size_t col = 0;
    while (colIt != values.end() && col < W) {
      auto rowIt = colIt->begin();
      size_t row = 0;
      while (rowIt != colIt->end() && row < H) {
        m_columns[col][row] = *rowIt;

        ++rowIt;
        ++row;
      }
      ++colIt;
      ++col;
    }
  }

  /// Cast to matrix with different element type.
  ///
  /// \return Matrix with casted element type
  template<typename T2>
  Matrix<T2, W, H> staticCast() const
  {
    Matrix<T2, W, H> result;

    for (size_t col = 0; col < W; col++) {
      const Vector<T, H>& columnIn = m_columns[col];
      Vector<T2, H>& columnOut = result[col];

      for (size_t row = 0; row < H; row++) {
        columnOut[row] = static_cast<T2>(columnIn[row]);
      }
    }

    return result;
  }

  // Compare operators

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other matrix
  /// \return True if equal, false otherwise
  bool operator==(const Matrix<T, W, H>& other) const
  {
    for (size_t col = 0; col < W; col++) {
      if (m_columns[col] != other[col]) {
        return false;
      }
    }
    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other matrix
  /// \return True if unequal, false otherwise
  bool operator!=(const Matrix<T, W, H>& other) const
  {
    return !(operator==(other));
  }

  // Data access

  /// Access column (vector).
  ///
  /// \return Column
  Vector<T, H>& operator[](const size_t index) { return m_columns[index]; }

  /// Access column (vector).
  ///
  /// \return Column
  const Vector<T, H>& operator[](const size_t index) const
  {
    return m_columns[index];
  }

  /// Get number of columns (width)
  ///
  /// \return Column count
  constexpr size_t cols() const noexcept { return W; }

  /// Get number of rows (height)
  ///
  /// \return Row count
  constexpr size_t rows() const noexcept { return H; }

  /// Get pointer to data.
  ///
  /// \return Data pointer
  T* data() noexcept { return m_columns[0].data(); }

  /// Get const pointer to data.
  ///
  /// \return Const data pointer
  const T* data() const noexcept { return m_columns[0].data(); }

  // Arithmetic operators

  /// Add another matrix.
  ///
  /// \param[in] other Matrix to add
  /// \return Added matrix
  Matrix<T, W, H> operator+(const Matrix<T, W, H>& other) const
  {
    Matrix<T, W, H> result;
    for (size_t col = 0; col < W; col++) {
      result[col] = m_columns[col] + other[col];
    }
    return result;
  }

  /// Subtract other matrix.
  ///
  /// \param[in] other Matrix to subtract
  /// \return Subtracted matrix
  Matrix<T, W, H> operator-(const Matrix<T, W, H>& other) const
  {
    Matrix<T, W, H> result;
    for (size_t col = 0; col < W; col++) {
      result[col] = m_columns[col] - other[col];
    }
    return result;
  }

  /// Multiply by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Multiplied vector
  Matrix<T, W, H> operator*(T scalar) const
  {
    Matrix<T, W, H> result;
    for (size_t col = 0; col < W; col++) {
      result[col] = m_columns[col] * scalar;
    }
    return result;
  }

  /// Divide by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Divided matrix
  Matrix<T, W, H> operator/(T scalar) const
  {
    Matrix<T, W, H> result;
    for (size_t col = 0; col < W; col++) {
      result[col] = m_columns[col] / scalar;
    }
    return result;
  }

  /// Multiply by matrix.
  ///
  /// \param[in] other Matrix to multiply with
  /// \return Multiplied matrix
  template<size_t W2>
  Matrix<T, W2, H> operator*(const Matrix<T, W2, W>& other) const
  {
    Matrix<T, W2, H> result;

    for (size_t i = 0; i < H; i++) {
      for (size_t j = 0; j < W2; j++) {
        T val = 0;
        for (size_t k = 0; k < W; k++) {
          val += m_columns[k][i] * other[j][k];
        }
        result[j][i] = val;
      }
    }

    return result;
  }

  /// Multiply by vector.
  ///
  /// \param[in] vector Vector to multiply with
  /// \return Multiplied vector
  Vector<T, H> operator*(const Vector<T, W>& vector) const
  {
    Vector<T, H> result;
    for (size_t i = 0; i < H; i++) {
      T val = 0;
      for (size_t j = 0; j < W; j++) {
        val += m_columns[j][i] * vector[j];
      }
      result[i] = val;
    }
    return result;
  }

  // Matrix operations

  /// Get transposed matrix.
  ///
  /// \return Transposed matrix
  Matrix<T, H, W> transposed() const
  {
    Matrix<T, H, W> result;
    for (size_t col = 0; col < W; col++) {
      for (size_t row = 0; row < H; row++) {
        result[row][col] = m_columns[col][row];
      }
    }
    return result;
  }

  /// Omit a given column and row.
  ///
  /// \param[out] col Column to omit
  /// \param[in] row Row to omit
  /// \return Matrix with omitted row and column
  Matrix<T, W - 1, H - 1> omit(size_t col, size_t row) const
  {
    Matrix<T, W - 1, H - 1> result;
    size_t colIndex = 0;
    size_t rowIndex = 0;

    // Iterate columns
    for (size_t i = 0; i < W; i++) {
      if (i != col) {
        rowIndex = 0;

        // Iterate rows
        for (size_t j = 0; j < H; j++) {
          if (j != row) {
            result[colIndex][rowIndex] = m_columns[i][j];
            rowIndex++;
          }
        } // end of row

        colIndex++;
      }
    }

    return result;
  }

  /// Calculate determinant.
  ///
  /// The determinant is calculated through expansion by minors for matrices
  /// larger than 3x3.
  ///
  /// \return Determinant
  template<typename U = T>
  spgl_enable_if_t<W == H && W >= 2 && W <= 4, U> determinant() const
  {
    return determinant(*this);
  }

  /// Calulcate minor
  ///
  /// The minor is the determinant of the matrix formed by omitting a given
  /// row and column.
  ///
  /// \param[in] row Row to omit
  /// \param[out] col Column to omit
  /// \return Minor
  T minor(size_t col, size_t row) const
  {
    const Matrix<T, W - 1, H - 1> t = omit(col, row);
    return t.determinant();
  }

  /// Calculate inverse of matrix.
  ///
  /// \throw std::out_of_range Matrix has no inverse
  /// \return Inverse of matrix
  template<typename U = T>
  spgl_enable_if_t<W == H && W >= 2 && W <= 4, Matrix<U, W, H>> inverse() const
  {
    const U det = determinant();
    if (det == 0) {
      throw std::out_of_range("Matrix has no inverse (matrix is singular)");
    }

    Matrix<U, W, H> result;
    for (size_t j = 0; j < H; j++) {
      for (size_t i = 0; i < W; i++) {
        Matrix<U, W - 1, H - 1> minor = omit(i, j);
        result[j][i] = minor.determinant() / det;
        if ((i + j) % 2 == 1) {
          result[j][i] = -result[j][i];
        }
      }
    }
    return result;
  }

  // Geometric operations

  // Projections

  /// Create orthographic projection matrix
  ///
  /// Project from orthographic view volume to canonical view volume.
  ///
  /// Beware: near and far should be negative and the following is true:
  /// 0 > near > far
  /// far is a negative number of larger absolute value than near.
  ///
  /// \param[in] size Orthographic size
  /// \param[in] aspect Aspect ratio (w/h)
  /// \param[in] near Distance to near clipping plane (Z coordinate)
  /// \param[in] far Distance to far clipping plane (Z coordinate)
  /// \return Orthographic projection matrix
  static Matrix<T, 4, 4> ortho(const T size,
                               const T aspect,
                               const T near,
                               const T far)
  {
    const T top = size * static_cast<T>(0.5);
    const T bottom = -top;
    const T right = size * static_cast<T>(0.5) * aspect;
    const T left = -right;

    return Matrix<T, 4, 4>::ortho(left, right, bottom, top, near, far);
  }

  /// Create orthographic projection matrix.
  ///
  /// Project from orthographic view volume to canonical view volume.
  ///
  /// \param[in] left Coordinate of left vertical clipping plane.
  /// \param[in] right Coordinate of right vertical clipping plane.
  /// \param[in] bottom Coordinate of bottom horizontal clipping plane.
  /// \param[in] top Coordinate of horizontal clipping plane.
  /// \param[in] near Distance to nearer depth clipping plane.
  /// \param[in] far Distances to farther depth clipping plane.
  /// \return Orthographic projection matrix
  static Matrix<T, 4, 4> ortho(const T left,
                               const T right,
                               const T bottom,
                               const T top,
                               const T near,
                               const T far)
  {
    Matrix<T, 4, 4> result(1);

    result[0][0] = static_cast<T>(2) / (right - left);
    result[1][1] = static_cast<T>(2) / (top - bottom);
    result[2][2] = -static_cast<T>(2) / (far - near);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(far + near) / (far - near);

    return result;
  }

  /// Create perspective projection matrix.
  ///
  /// Project from view frustrum to canonical view volumne.
  ///
  /// \param[in] fovy Vertical field of view angle (radians)
  /// \param[in] aspect Aspect ratio (w/h)
  /// \param[in] near Distance to near clipping plane (Z coordinate)
  /// \param[in] far Distance to far clipping plane (Z coordinate)
  /// \return Perspective projection matrix
  static Matrix<T, 4, 4> perspective(const T fovy,
                                     const T aspect,
                                     const T near,
                                     const T far)
  {
    Matrix<T, 4, 4> result;

    const T tanHalfFovy = tan(fovy / static_cast<T>(2));

    result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
    result[1][1] = static_cast<T>(1) / (tanHalfFovy);
    result[2][2] = -(far + near) / (far - near);
    result[2][3] = -static_cast<T>(1);
    result[3][2] = -(static_cast<T>(2) * far * near) / (far - near);

    return result;
  }

  /// Create viewport transform matrix.
  ///
  /// Transform from normalized device coordinates (NDC) to screen coordinates.
  /// NDC are in range [-1, 1]. Bottom left corner is (-1, -1) and top right
  /// corner is (1,1).
  /// Screen coordinates are in range [0, width] and [0, height]. Bottom left
  /// corner is (0,0) and top right corner is (idth, heigth)
  ///
  /// Note: this is a 2D transformation. Z=0.
  ///
  /// \param[in] size Screen size
  /// \return Vieport transform matrix
  template<typename T2>
  static Matrix<T, 4, 4> viewport(const Vector<T2, 2>& size)
  {
    Matrix<T, 4, 4> result;

    const T w = static_cast<T>(size[0]);
    const T h = static_cast<T>(size[1]);

    result[0][0] = w / 2;
    result[1][1] = h / 2;
    result[2][2] = 1;
    result[3][0] = w / 2; // (w-1)
    result[3][1] = h / 2; // (h-1)
    result[3][3] = 1;

    return result;
  }

  // Construct affine transformation matrix 4x4

  /// Construct translation matrix.
  ///
  /// \param[in] x Translation on X axis
  /// \param[in] y Translation on Y axis
  /// \param[in] z Translation on Z axis
  /// \return Translation matrix
  static Matrix<T, 4, 4> translation(const T x, const T y, const T z)
  {
    Matrix<T, 4, 4> result;
    result[3][0] = x;
    result[3][1] = y;
    result[3][2] = z;
    result[0][0] = static_cast<T>(1);
    result[1][1] = static_cast<T>(1);
    result[2][2] = static_cast<T>(1);
    result[3][3] = static_cast<T>(1);
    return result;
  }

  /// Construct scaling matrix.
  ///
  /// \param[in] x Scaling on X axis
  /// \param[in] y Scaling on Y axis
  /// \param[in] z Scaling on Z axis
  /// \return Scaling matrix
  static Matrix<T, 4, 4> scaling(const T x, const T y, const T z)
  {
    Matrix<T, 4, 4> result;
    result[0][0] = x;
    result[1][1] = y;
    result[2][2] = z;
    result[3][3] = static_cast<T>(1);
    return result;
  }

  /// Construct rotation matrix (counterclockwise).
  ///
  /// Rotation ordering: X -> Y -> Z
  ///
  /// \param[in] x Rotation on X axis
  /// \param[in] y Rotation on Y axis
  /// \param[in] z Rotation on Z axis
  /// \return Rotation matrix
  static Matrix<T, 4, 4> rotation(const T x, const T y, const T z)
  {
    return Matrix<T, 4, 4>::rotationZ(z) * Matrix<T, 4, 4>::rotationY(y) *
           Matrix<T, 4, 4>::rotationX(x);
  }

  /// Construct matrix for rotation around X axis (counterclockwise).
  ///
  /// \param[in] angle Angle in radians
  /// \return Rotation matrix
  static Matrix<T, 4, 4> rotationX(const T angle)
  {
    Matrix<T, 4, 4> result;
    result[0][0] = static_cast<T>(1);
    result[1][1] = cos(angle);
    result[2][1] = -sin(angle); // +?
    result[1][2] = sin(angle);  // -?
    result[2][2] = cos(angle);
    result[3][3] = static_cast<T>(1);
    return result;
  }

  /// Construct matrix for rotation around Y axis (counterclockwise).
  ///
  /// \param[in] angle Angle in radians
  /// \return Rotation matrix
  static Matrix<T, 4, 4> rotationY(const T angle)
  {
    Matrix<T, 4, 4> result;
    result[0][0] = cos(angle);
    result[1][1] = static_cast<T>(1);
    result[2][0] = sin(angle);
    result[0][2] = -sin(angle);
    result[2][2] = cos(angle);
    result[3][3] = static_cast<T>(1);
    return result;
  }

  /// Construct matrix for rotation around Z axis (counterclockwise).
  ///
  /// \param[in] angle Angle in radians
  /// \return Rotation matrix
  static Matrix<T, 4, 4> rotationZ(const T angle)
  {
    Matrix<T, 4, 4> result;
    result[0][0] = cos(angle);
    result[1][0] = -sin(angle); // +?
    result[0][1] = sin(angle);  // -?
    result[1][1] = cos(angle);
    result[2][2] = static_cast<T>(1);
    result[3][3] = static_cast<T>(1);
    return result;
  }

  /// Construct matrix for rotation around axis (counterclockwise).
  ///
  /// \param[in] axis Axis vector
  /// \param[in] angle Angle in radians
  /// \return Rotation matrix
  static Matrix<T, 4, 4> rotationAround(const Vector<T, 3>& axis, T angle)
  {
    Matrix<T, 4, 4> result;

    const Vector<T, 3> axisNormalized = axis.normalized();
    const T q0 = cos(angle / 2);
    const T q1 = sin(angle / 2) * axisNormalized.x();
    const T q2 = sin(angle / 2) * axisNormalized.y();
    const T q3 = sin(angle / 2) * axisNormalized.z();

    // Column 0
    result[0][0] = q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3;
    result[0][1] = 2 * (q2 * q1 + q0 * q3);
    result[0][2] = 2 * (q3 * q1 - q0 * q2);
    result[0][3] = 0;

    // Column 1
    result[1][0] = 2 * (q1 * q2 - q0 * q3);
    result[1][1] = (q0 * q0 - q1 * q1 + q2 * q2 - q3 * q3);
    result[1][2] = 2 * (q3 * q2 + q0 * q1);
    result[1][3] = 0;

    // Column 2
    result[2][0] = 2 * (q1 * q3 + q0 * q2);
    result[2][1] = 2 * (q2 * q3 - q0 * q1);
    result[2][2] = (q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3);
    result[2][3] = 0;

    // Column 3
    result[3][0] = 0;
    result[3][1] = 0;
    result[3][2] = 0;
    result[3][3] = 1;

    return result;
  }

  /// Output to ostream
  friend std::ostream& operator<<(std::ostream& os,
                                  const Matrix<T, W, H>& matrix)
  {
    os << "Matrix(" << W << "," << H << ")\n";
    for (size_t row = 0; row < H; row++) {
      for (size_t col = 0; col < W; col++) {
        os << matrix[col][row] << " ";
      }
      os << "\n";
    }

    return os;
  }

protected:
  /// Calculate determinant of 4x4 matrix.
  ///
  /// Recursive function.
  ///
  /// \param[in] matrix Matrix
  /// \return Determinant
  T determinant(const Matrix<T, 4, 4>& matrix) const
  {
    T det = 0;
    for (size_t i = 0; i < 4; i++) {
      Matrix<T, 3, 3> minor = omit(i, 0);
      det += (i % 2 == 1 ? -1.0 : 1.0) * matrix[i][0] * minor.determinant();
    }
    return det;
  }

  /// Calculate determinant of 3x3 matrix.
  ///
  /// \param[in] matrix Matrix
  /// \return Determinant
  T determinant(const Matrix<T, 3, 3>& matrix) const
  {
    return matrix[0][0] *
             (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) -
           matrix[1][0] *
             (matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2]) +
           matrix[2][0] *
             (matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]);
  }

  /// Calculate determinant of 2x2 matrix.
  ///
  /// \param[in] matrix Matrix
  /// \return Determinant
  T determinant(const Matrix<T, 2, 2>& matrix) const
  {
    return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
  }

private:
  std::array<Vector<T, H>, W> m_columns;
};

/// Matrix of 2x2 with double precision elements
using Matrix2 = Matrix<double, 2, 2>;

/// Matrix of 2x2 with single precision elements
using Matrix2f = Matrix<float, 2, 2>;

/// Matrix of 3x3 with double precision elements
using Matrix3 = Matrix<double, 3, 3>;

/// Matrix of 2x2 with single precision elements
using Matrix3f = Matrix<float, 3, 3>;

/// Matrix of 4x4 with double precision elements
using Matrix4 = Matrix<double, 4, 4>;

/// Matrix of 4x4 with single precision elements
using Matrix4f = Matrix<float, 4, 4>;

} // namespace spgl

/*
template<typename T, size_t W, size_t H>
struct SPATIUMGL_EXPORT MatrixBase
{
public:
  /// Access column (vector).
  ///
  /// \return Column reference
  Vector<T, H>& operator[](const size_t index) { return m_data[index]; }

  /// Access column (vector)
  ///
  /// \return Column const reference
  const Vector<T, H>& operator[](const size_t index) const
  {
    return m_data[index];
  }

  /// Get number of columns (width)
  ///
  /// \return Column count
  constexpr size_t cols() const noexcept { return W; }

  /// Get number of rows (height)
  ///
  /// \return Row count
  constexpr size_t rows() const noexcept { return H; }

  /// Get pointer to data.
  ///
  /// \return Data pointer
  T* data() noexcept { return m_data[0].data(); }

  /// Get const pointer to data.
  ///
  /// \return Const data pointer
  const T* data() const noexcept { return m_data[0].data(); }

  /// Clear all values (set to 0).
  void clear()
  {
    // ERROR: std::fill(std::begin(m_data), std::end(m_data), 0);
  }

protected:
  // Hide constructor to prevent declaration
  MatrixBase()
    : m_data()
  {}

  MatrixBase(std::initializer_list<std::initializer_list<T>> data)
    : m_data()
  {
    // Iterate columns
    size_t col = 0;
    auto colIt = data.begin();
    while (col < W && colIt != data.end()) {
      Vector<T, H>& column = m_data[col];

      // Iterate rows
      size_t row = 0;
      auto rowIt = colIt->begin();
      while (row < H && rowIt != colIt->end()) {
        // Copy value
        column[row] = *rowIt;

        ++row;
        ++rowIt;
      }

      ++col;
      ++colIt;
    }
  }

  Vector<T, H> m_data[W]; /// \todo std::array
};

template<typename T, size_t W, size_t H>
struct SPATIUMGL_EXPORT Matrix : public MatrixBase<T, W, H>
{
  constexpr Matrix() = default;

  /// \TODO Add all matrix functionality that is also in Matrix2, Matrix3 and
  /// Matrix4

  template<typename T2>
  Matrix<T2, W, H> staticCast() const
  {
    Matrix<T2, W, H> result;

    for (size_t col = 0; col < W; col++) {
      const Vector<T, H>& columnIn = this->m_data[col];
      Vector<T, H>& columnOut = result[col];

      for (size_t row = 0; row < H; row++) {
        columnOut[row] = static_cast<T2>(columnIn[row]);
      }
    }

    return result;
  }

  /// Output to ostream (untested)
  friend std::ostream& operator<<(std::ostream& os,
                                  const Matrix<T, W, H>& matrix)
  {
    os << "Matrix(" << W << ", " << H << ")"
       << "\n";
    for (size_t row = 0; row < H; row++) {
      for (size_t col = 0; col < W; col++) {
        os << matrix[col][row] << " ";
      }
      os << "\n";
    }
    return os;
  }
};
}

#include "Matrix2x2.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"

namespace spgl {
using Matrix2 = Matrix<double, 2, 2>;
using Matrix3 = Matrix<double, 3, 3>;
using Matrix4 = Matrix<double, 4, 4>;

using Matrix2f = Matrix<float, 2, 2>;
using Matrix3f = Matrix<float, 3, 3>;
using Matrix4f = Matrix<float, 4, 4>;
}

*/

#endif // SPATIUMGL_MATRIX_H
