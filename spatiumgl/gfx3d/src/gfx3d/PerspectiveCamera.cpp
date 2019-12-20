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

#include "spatiumgl/gfx3d/PerspectiveCamera.hpp"

namespace spgl {
namespace gfx3d {

PerspectiveCamera::PerspectiveCamera(double fov, double near, double far)
  : Camera(near, far)
  , m_fov(fov)
{}

void
PerspectiveCamera::setFov(double fov)
{
  m_fov = fov;
}

double
PerspectiveCamera::fov() const
{
  return m_fov;
}

Matrix4
PerspectiveCamera::projectionMatrix(double aspect) const
{
  return Matrix4::perspective(m_fov, aspect, m_near, m_far);
}

Vector3
PerspectiveCamera::worldToViewportPoint(const Vector3& point,
                                        const double aspect) const
{
  const Matrix4 view = transform().matrix().inverse();
  const Matrix4 projection = projectionMatrix(aspect);
  const Vector4 viewportPoint = projection * view * Vector4(point, 1);
  return { viewportPoint.x(), viewportPoint.y(), viewportPoint.z() };
}

Vector3
PerspectiveCamera::worldToScreenPoint(const Vector3& point,
                                      const Vector2i& size) const
{
  const double w = static_cast<double>(size.x());
  const double h = static_cast<double>(size.y());
  const Vector3 viewportPoint = worldToViewportPoint(point, w / h);
  const Matrix4 viewportMatrix = Matrix4::viewport(size);
  const Vector4 screenPoint = viewportMatrix * Vector4(viewportPoint, 1);
  return { screenPoint.x(), screenPoint.y(), screenPoint.z() };
}

} // namespace gfx3d
} // namespace spgl
