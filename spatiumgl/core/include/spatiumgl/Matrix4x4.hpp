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

#ifndef SPATIUMGL_MATRIX4X4_H
#define SPATIUMGL_MATRIX4X4_H

#include "Matrix.hpp"

#ifdef __linux__
#undef minor
#endif

namespace spatiumgl {
template<typename T>
struct SPATIUMGL_EXPORT Matrix<T, 4, 4> : public MatrixBase<T, 4, 4>
{
  /// Default constructor
  ///
  /// Sets all elements to 0.
  Matrix() = default;

  /// Constructor
  ///
  /// Sets all elements to 0 except diagonal elements.
  ///
  /// \param[in] diagional Diagonal value
  Matrix(T diagional)
    : MatrixBase<T, 4, 4>()
  {
    this->m_data[0][0] = diagional;
    this->m_data[1][1] = diagional;
    this->m_data[2][2] = diagional;
    this->m_data[3][3] = diagional;
  }

  /// Constructor
  ///
  /// \param[in] Data Initializer list with column-major ordering.
  constexpr Matrix(std::initializer_list<std::initializer_list<T>> data)
    : MatrixBase<T, 4, 4>(data)
  {}

  /// Cast to matrix with different element type (static_cast).
  ///
  /// \return Matrix with cast element type
  template<typename T2>
  Matrix<T2, 4, 4> staticCast() const
  {
    Matrix<T2, 4, 4> result;

    // Column 0
    result[0][0] = static_cast<T2>(this->m_data[0][0]);
    result[0][1] = static_cast<T2>(this->m_data[0][1]);
    result[0][2] = static_cast<T2>(this->m_data[0][2]);
    result[0][3] = static_cast<T2>(this->m_data[0][3]);

    // Column 1
    result[1][0] = static_cast<T2>(this->m_data[1][0]);
    result[1][1] = static_cast<T2>(this->m_data[1][1]);
    result[1][2] = static_cast<T2>(this->m_data[1][2]);
    result[1][3] = static_cast<T2>(this->m_data[1][3]);

    // Column 2
    result[2][0] = static_cast<T2>(this->m_data[2][0]);
    result[2][1] = static_cast<T2>(this->m_data[2][1]);
    result[2][2] = static_cast<T2>(this->m_data[2][2]);
    result[2][3] = static_cast<T2>(this->m_data[2][3]);

    // Column 3
    result[3][0] = static_cast<T2>(this->m_data[3][0]);
    result[3][1] = static_cast<T2>(this->m_data[3][1]);
    result[3][2] = static_cast<T2>(this->m_data[3][2]);
    result[3][3] = static_cast<T2>(this->m_data[3][3]);

    return result;
  }

  // Compare operators

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other matrix
  /// \return True if equal, otherwise false
  bool operator==(const Matrix<T, 4, 4>& other) const
  {
    if (this->m_data[0] != other.m_data[0] ||
        this->m_data[1] != other.m_data[1] ||
        this->m_data[2] != other.m_data[2] ||
        this->m_data[3] != other.m_data[3]) {
      return false;
    } else {
      return true;
    }
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other matrix
  /// \return True if unequal, otherwise false
  bool operator!=(const Matrix<T, 4, 4>& other) const
  {
    return !(operator==(other));
  }

  // Arithmetic operators

  /// Add another matrix.
  ///
  /// \param[in] other Matrix to add
  /// \return Added matrix
  Matrix<T, 4, 4> operator+(const Matrix<T, 4, 4>& other) const
  {
    Matrix<T, 4, 4> result;
    result[0][0] = this->m_data[0][0] + other[0][0];
    result[0][1] = this->m_data[0][1] + other[0][1];
    result[0][2] = this->m_data[0][2] + other[0][2];
    result[0][3] = this->m_data[0][3] + other[0][3];
    result[1][0] = this->m_data[1][0] + other[1][0];
    result[1][1] = this->m_data[1][1] + other[1][1];
    result[1][2] = this->m_data[1][2] + other[1][2];
    result[1][3] = this->m_data[1][3] + other[1][3];
    result[2][0] = this->m_data[2][0] + other[2][0];
    result[2][1] = this->m_data[2][1] + other[2][1];
    result[2][2] = this->m_data[2][2] + other[2][2];
    result[2][3] = this->m_data[2][3] + other[2][3];
    result[3][0] = this->m_data[3][0] + other[3][0];
    result[3][1] = this->m_data[3][1] + other[3][1];
    result[3][2] = this->m_data[3][2] + other[3][2];
    result[3][3] = this->m_data[3][3] + other[3][3];
    return result;
  }

  /// Subtract other matrix.
  ///
  /// \param[in] other Matrix to subtract
  /// \return Subtracted matrix
  Matrix<T, 4, 4> operator-(const Matrix<T, 4, 4>& other) const
  {
    Matrix<T, 4, 4> result;
    result[0][0] = this->m_data[0][0] - other[0][0];
    result[0][1] = this->m_data[0][1] - other[0][1];
    result[0][2] = this->m_data[0][2] - other[0][2];
    result[0][3] = this->m_data[0][3] - other[0][3];
    result[1][0] = this->m_data[1][0] - other[1][0];
    result[1][1] = this->m_data[1][1] - other[1][1];
    result[1][2] = this->m_data[1][2] - other[1][2];
    result[1][3] = this->m_data[1][3] - other[1][3];
    result[2][0] = this->m_data[2][0] - other[2][0];
    result[2][1] = this->m_data[2][1] - other[2][1];
    result[2][2] = this->m_data[2][2] - other[2][2];
    result[2][3] = this->m_data[2][3] - other[2][3];
    result[3][0] = this->m_data[3][0] - other[3][0];
    result[3][1] = this->m_data[3][1] - other[3][1];
    result[3][2] = this->m_data[3][2] - other[3][2];
    result[3][3] = this->m_data[3][3] - other[3][3];
    return result;
  }

  /// Multiply by scalar.
  // TODO

  /// Divide by scalar.
  // TODO

  /// Multiply by vector.
  ///
  /// \param[in] vector Vector to multiply with
  /// \return Multiplied vector
  Vector<T, 4> operator*(const Vector<T, 4>& vector) const
  {
    Vector<T, 4> result;
    result[0] = this->m_data[0][0] * vector[0] +
                this->m_data[1][0] * vector[1] +
                this->m_data[2][0] * vector[2] + this->m_data[3][0] * vector[3];
    result[1] = this->m_data[0][1] * vector[0] +
                this->m_data[1][1] * vector[1] +
                this->m_data[2][1] * vector[2] + this->m_data[3][1] * vector[3];
    result[2] = this->m_data[0][2] * vector[0] +
                this->m_data[1][2] * vector[1] +
                this->m_data[2][2] * vector[2] + this->m_data[3][2] * vector[3];
    result[3] = this->m_data[0][3] * vector[0] +
                this->m_data[1][3] * vector[1] +
                this->m_data[2][3] * vector[2] + this->m_data[3][3] * vector[3];
    return result;
  }

  /// Multiply by matrix.
  ///
  /// \param[in] other Matrix to multiply with
  /// \return Multiplied matrix
  template<size_t W2>
  Matrix<T, 4, W2> operator*(const Matrix<T, W2, 4>& other) const
  {
    Matrix<T, 4, W2> result;

    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < W2; j++) {
        T val = static_cast<T>(0);
        for (size_t k = 0; k < 4; k++) {
          val += this->m_data[k][i] * other[j][k];
        }
        result[j][i] = val;
      }
    }

    return result;
  }

  // Matrix operations

  /// Get transposed matrix.
  ///
  /// \return Transposed matrix
  Matrix<T, 4, 4> transposed() const
  {
    Matrix<T, 4, 4> result;
    result[0][0] = this->m_data[0][0];
    result[0][1] = this->m_data[1][0];
    result[0][2] = this->m_data[2][0];
    result[0][3] = this->m_data[3][0];
    result[1][0] = this->m_data[0][1];
    result[1][1] = this->m_data[1][1];
    result[1][2] = this->m_data[2][1];
    result[1][3] = this->m_data[3][1];
    result[2][0] = this->m_data[0][2];
    result[2][1] = this->m_data[1][2];
    result[2][2] = this->m_data[2][2];
    result[2][3] = this->m_data[3][2];
    result[3][0] = this->m_data[0][3];
    result[3][1] = this->m_data[1][3];
    result[3][2] = this->m_data[2][3];
    result[3][3] = this->m_data[3][3];
    return result;
  }

  /// Omit a given row and column.
  ///
  /// \param[in] row Row to omit
  /// \param[out] col Column to omit
  /// \return Matrix with omitted row and column
  Matrix<T, 3, 3> omit(const size_t col, const size_t row) const
  {
    Matrix<T, 3, 3> result;
    size_t colCount = 0, rowCount = 0;
    for (size_t i = 0; i < 4; i++) {
      if (i != row) {
        colCount = 0;
        for (size_t j = 0; j < 4; j++) {
          if (j != col) {
            result[colCount][rowCount] = this->m_data[j][i];
            colCount++;
          }
        }
        rowCount++;
      }
    }

    return result;
  }

  /// Calculate determinant.
  ///
  /// \return Determinant
  T determinant() const
  {
    T det = 0;
    for (size_t i = 0; i < 4; i++) {
      Matrix<T, 3, 3> minor = omit(i, 0);
      det +=
        (i % 2 == 1 ? -1.0 : 1.0) * this->m_data[i][0] * minor.determinant();
    }
    return det;
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
    const Matrix<T, 3, 3> t = omit(col, row);
    return t.determinant();
  }

  /// Calculate inverse of matrix.
  ///
  /// \throw std::out_of_range Matrix has no inverse
  /// \return Inverse of matrix
  Matrix<T, 4, 4> inverse() const
  {
    const T det = determinant();
    if (det == 0) {
      throw std::out_of_range("Matrix has no inverse (matrix is singular)");
    }

    Matrix<T, 4, 4> result;
    for (size_t j = 0; j < 4; j++) {
      for (size_t i = 0; i < 4; i++) {
        Matrix<T, 3, 3> minor = omit(i, j);
        const T r = minor.determinant() / det;
        result[j][i] = r;
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

  // Construct affine transformation Matrix4x4

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
                                  const Matrix<T, 4, 4>& matrix)
  {
    os << "Matrix(4,4)"
       << "\n";
    os << matrix[0][0] << " " << matrix[1][0] << " " << matrix[2][0] << " "
       << matrix[3][0] << "\n";
    os << matrix[0][1] << " " << matrix[1][1] << " " << matrix[2][1] << " "
       << matrix[3][1] << "\n";
    os << matrix[0][2] << " " << matrix[1][2] << " " << matrix[2][2] << " "
       << matrix[3][2] << "\n";
    os << matrix[0][3] << " " << matrix[1][3] << " " << matrix[2][3] << " "
       << matrix[3][3] << "\n";
    return os;
  }
};
}

#endif // SPATIUMGL_MATRIX4X4_H
