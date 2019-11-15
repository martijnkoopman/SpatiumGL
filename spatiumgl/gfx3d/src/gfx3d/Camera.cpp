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

#include "spatiumgl/gfx3d/Camera.hpp"

#include <algorithm> // std::max

namespace spatiumgl {
namespace gfx3d {
Camera::Camera(double near, double far)
  : SceneObject()
  , m_near(near)
  , m_far(far)
{}

/// Get the distance to the near clipping plane in world space.
///
/// \return Near clipping plane distance.
double
Camera::near() const
{
  return m_near;
}

/// Get the distance to the far clipping plane in world space.
///
/// \return Far clipping plane distance.
double
Camera::far() const
{
  return m_far;
}

/// Set view direction towards target position.
/// The resulting transformation matrix maps the reference point to the
/// negative z axis and the eye point to the origin.
///
/// \param[in] target Target position
/// \param[in] up Up vector
///                May not be parallel with view direction vector
void
Camera::lookAt(const Vector3& target, const Vector3& up)
{
  // Compute vector from target to eye
  Vector3 back = (m_transform.translation() - target).normalized();

  // Normalize and orthogonalize view up vector
  Vector3 right = Vector3(up.normalized()).cross(back);
  Vector3 upOrtho = back.cross(right);

  // Set rotation of transformation matrix based on view direction and view
  // up vector.
  Matrix4 M = m_transform.matrix();

  // First COLUMN is right vector
  M[0] = Vector4(right, 0.0);

  // Second COLUMN is up vector
  M[1] = Vector4(upOrtho, 0.0);

  // Third COLUMN is back vector
  M[2] = Vector4(back, 0.0);

  m_transform.setMatrix(M);
}

/// Set camera position and set view direction towards target position.
/// The resulting transformation matrix maps the reference point to the
/// negative z axis and the eye point to the origin.
///
/// \param[in] eye Camera/eye position
/// \param[in] target Target position
/// \param[in] up Up vector
///                May not be parallel with vector from eye to target
void
Camera::lookAt(const Vector3& target, const Vector3& up, const Vector3& eye)
{
  m_transform.setTranslation(eye);
  lookAt(target, up);
}

void
Camera::orthogonalizeViewUp()
{
  Vector3 upOrtho = m_transform.back().cross(m_transform.right());

  Matrix4 M = m_transform.matrix();

  // Second COLUMN is up vector
  M[1] = Vector4(upOrtho, 0.0);

  m_transform.setMatrix(M);
}

void
Camera::setNearAndFarFromBounds(const BoundingBox<double>& bounds)
{
  // Compute radius from bounds
  const Vector3 radii = bounds.radii();
  const double radius = std::max({ radii[0], radii[1], radii[2] });

  // Check camera in bounds?
  const Vector3 cameraTranslation = m_transform.translation();
  if (bounds.isInside(cameraTranslation)) {
    // Compute and set near and far clipping plane distances
    m_far = 2 * radius;
    m_near = m_far / 1000;
  } else {
    // Compute distance to center of bounds
    const double distance = (bounds.center() - cameraTranslation).length();

    // Compute and set near and far clipping plane distances
    m_far = distance + radius;
    m_near = distance - radius;
    if (m_near <= 0) {
      m_near = m_far / 1000;
    }
  }
}

} // namespace gfx3d
} // namespace spatiumgl
