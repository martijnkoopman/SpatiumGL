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

#ifndef SPATIUMGL_GFX3D_TRANSFORM_H
#define SPATIUMGL_GFX3D_TRANSFORM_H

#include "spatiumgl/Matrix.hpp"
#include "spatiumgl/Vector.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

/// \class Transform
/// \brief Tranformation in 3D space.
///
/// Default transformation matrix (identity):
///
/// 1 0 0 x
/// 0 1 0 y
/// 0 0 1 z
/// 0 0 0 1
///
/// 1st column = right vector
/// 2nd column = up vector
/// 3rd column = back vector
/// 4rd column = translation (position)
class SPATIUMGL_EXPORT Transform
{
public:
  /// Default constructor
  Transform();

  /// Get the vector pointing to the right (positive X axis)
  ///
  /// \return Right vector
  Vector3 right() const;

  /// Get the vector pointing up (positive y axis)
  ///
  /// \return Up vector
  Vector3 up() const;

  /// Get the vector pointing back (positive z axis)
  ///
  /// \return Back vector
  Vector3 back() const;

  /// Clear the transformation.
  ///
  /// Reset transformation matrix to identity matrix.
  void clear();

  /// Get the position in world space (translation)
  ///
  /// \return Position
  Vector3 translation() const;

  /// Set the position in world space (translation)
  ///
  /// \param[in] position Position
  void setTranslation(const Vector3& translation);

  /// Apply translation.
  ///
  /// The translation is added.
  ///
  /// \param[in] translation Translation
  void translate(const Vector3& translation);

  /// \TODO setRotation(), rotation(), applyRotation(), setScale(), scale(),
  /// applyScale()

  /// Rotate around axis (relative to self/object space)
  ///
  /// \param[in] axis Axis vector
  /// \param[in] angle Angle in radians
  void rotateAround(const Vector3& axis, double angle);

  /// Rotate around X, Y and Z axis.
  ///
  /// In that order. (relative to self/object space)
  ///
  /// \param[in] x Angle around X axis in radians
  /// \param[in] y Angle around Y axis in radians
  /// \param[in] z Angle around Z axis in radians
  void rotate(double x, double y, double z);

  /// Rotate around X axis (relative to self/object space)
  ///
  /// \param[in] angle Angle in radians
  void rotateX(double angle);

  /// Rotate around Y axis (relative to self/object space)
  ///
  /// \param[in] angle Angle in radians
  void rotateY(double angle);

  /// Rotate around Z axis (relative to self/object space)
  ///
  /// \param[in] angle Angle in radians
  void rotateZ(double angle);

  /// Set the transformation matrix.
  ///
  /// \param[in] matrix Transformation matrix
  void setMatrix(const Matrix4& matrix);

  /// Get the transformation matrix (by reference)
  ///
  /// Beware: Direct manipulation of the matrix might invalidate the
  /// transformation, making it impossible to render the object. It
  /// is safer to make use of the convenience functions provided by
  /// this Transform class.
  ///
  /// \return Transformation matrix
  Matrix4& matrix();

  /// Get the transformation matrix (by const reference)
  ///
  /// \return Transformation matrix
  const Matrix4& matrix() const;

  /// Convert 3D Cartesian point coordinates from object space to world space.
  ///
  /// Object coordinates are defined with respect to the object's local
  /// coordinate system.
  /// World coordinates are defined with resect to the world's global
  /// cordinate system. (Origin = [0,0,0])
  ///
  /// \param[in] point Point cordinates in object space
  /// \return Point coordinates in world space
  Vector3 objectPointToWorldPoint(const Vector3& point) const;

  /// Convert 3D Cartesian point coordinates from world space to object space.
  ///
  /// World coordinates are defined with resect to the world's global
  /// cordinate system. (Origin = [0,0,0])
  /// Object coordinates are defined with respect to the object's local
  /// coordinate system.
  ///
  /// \param[in] point Point cordinates in world space
  /// \return Point coordinates in object space
  Vector3 worldPointToObjectPoint(const Vector3& point) const;

protected:
  /// Transformation matrix
  Matrix4 m_matrix;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_TRANSFORM_H
