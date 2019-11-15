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

#include "spatiumgl/gfx3d/Transform.hpp"

namespace spatiumgl {
namespace gfx3d {

Transform::Transform()
  : m_matrix(1) // identity matrix
{}

Vector3
Transform::right() const
{
  return { m_matrix[0][0], m_matrix[0][1], m_matrix[0][2] };
}

Vector3
Transform::up() const
{
  return { m_matrix[1][0], m_matrix[1][1], m_matrix[1][2] };
}

Vector3
Transform::back() const
{
  return { m_matrix[2][0], m_matrix[2][1], m_matrix[2][2] };
}

void
Transform::clear()
{
  m_matrix = Matrix4(1);
}

Vector3
Transform::translation() const
{
  return { m_matrix[3][0], m_matrix[3][1], m_matrix[3][2] };
}

void
Transform::setTranslation(const Vector3& translation)
{
  m_matrix[3] = Vector4(translation, 1.0);
}

void
Transform::translate(const Vector3& translation)
{
  m_matrix[3] = m_matrix[3] + Vector4(translation, 0);
  // m_matrix[3][3] = 1;
}

/*
/// Translate in world space
///
/// \param[in] xyz Translation on X, Y and Z axis
void translate(const geom3d::Vector3 &xyz)
{
  m_matrix(0,3) = m_matrix(0,3) + xyz.x();
  m_matrix(1,3) = m_matrix(1,3) + xyz.y();
  m_matrix(2,3) = m_matrix(2,3) + xyz.z();
}

/// Get the scale
///
/// \return Scale on x, y and z axis
geom3d::Vector3 scale() const
{
  const geom3d::Matrix4 &M = m_matrix;
  double x = geom3d::Vector3(M(0,0), M(1,0), M(2,0)).length(); // 1st column
  double y = geom3d::Vector3(M(0,1), M(1,1), M(2,1)).length(); // 2nd column
  double z = geom3d::Vector3(M(0,2), M(1,2), M(2,2)).length(); // 3rd column
  return geom3d::Vector3(x,y,z);
}

/// Rotate (relative to self/object space)
///
/// \param[in] euler Degrees around x, y and z axis
void rotate(const geom3d::Vector3 &euler)
{
  ///\todo This doesn't work... Use TRS?
  m_matrix = m_matrix * geom3d::Matrix4::rotation(euler.x(), euler.y(),
euler.z());
}
*/

void
Transform::rotateAround(const Vector3& axis, const double angle)
{
  m_matrix = Matrix4::rotationAround(axis, angle) * m_matrix;
}

void
Transform::rotate(const double x, const double y, const double z)
{
  m_matrix = Matrix4::rotation(x, y, z) * m_matrix;
}

void
Transform::rotateX(const double angle)
{
  m_matrix = Matrix4::rotationX(angle) * m_matrix;
}

void
Transform::rotateY(const double angle)
{
  m_matrix = Matrix4::rotationY(angle) * m_matrix;
}

void
Transform::rotateZ(const double angle)
{
  m_matrix = Matrix4::rotationZ(angle) * m_matrix;
}

/*
/// Set the rotation in world space
///
/// \param[in] euler Rotation in euler angles
void setRotation(const geom3d::Vector3 &euler)
{
  // Extract scale and translation from current matrix
  geom3d::Vector3 s = scale();
  geom3d::Point3 t = position();

  // Create translation, rotation and scale matrix
  geom3d::Matrix4 T = geom3d::Matrix4::translation(t.x(), t.y(), t.z());
  geom3d::Matrix4 R = geom3d::Matrix4::rotation(euler.x(), euler.y(),
euler.z()); geom3d::Matrix4 S = geom3d::Matrix4::scaling(s.x(), s.y(), s.z());

  // Constrcut matrix (scale first, then rotate, then translate)
  m_matrix = T * R * S;
}

/// Get the rotation in world space
///
/// \return Rotation in euler angles
geom3d::Vector3 rotation() const
{
  ///\todo Check if should each column should be scaled first?

  // Extract euler angles from matrix
  double x, y, z;
  const geom3d::Matrix4 &M = m_matrix;
  if (M(2,0) != 1 && M(2,0) != -1) ///\todo Unsafe compare
  {
  y = -asin(M(2,0));
  x = atan2(M(2,1) / cos(y), M(2,2) / cos(y));
  z = atan2(M(1,0) / cos(y), M(0,0) / cos(y));

  // There is a second solution:
  //theta = spatium::PI - theta;
  //psi = atan2( M(2,1) / cos(theta), M(2,2) / cos(theta));
  //phi = atan2( M(1,0) / cos(theta), M(0,0) / cos(theta));
  }
  else
  {
  // There is an infinit amount of solutions
  // Z can have an arbitrary value
  z = 0;
  if (M(2,0) == -1) ///\todo Unsafe compare
  {
    y = spatium::PI / 2;
    x = z + atan2(M(0,1), M(0,2));
  }
  else
  {
    y = -spatium::PI / 2;
    x = -z + atan2(-M(0,1), -M(0,2));
  }
  }

  return geom3d::Vector3(x,y,z);
}
*/

void
Transform::setMatrix(const Matrix4& matrix)
{
  m_matrix = matrix;
}

Matrix4&
Transform::matrix()
{
  return m_matrix;
}

const Matrix4&
Transform::matrix() const
{
  return m_matrix;
}

Vector3
Transform::objectPointToWorldPoint(const Vector3& point) const
{
  Vector4 result = m_matrix * Vector4(point, 1.0);
  return { result[0], result[1], result[2] };
}

Vector3
Transform::worldPointToObjectPoint(const Vector3& point) const
{
  Vector4 result = m_matrix.inverse() * Vector4(point, 1.0);
  return { result[0], result[1], result[2] };
}

} // namespace gfx3d
} // namespace spatiumgl
