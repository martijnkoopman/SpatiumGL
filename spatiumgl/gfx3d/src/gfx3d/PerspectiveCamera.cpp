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

} // namespace gfx3d
} // namespace spgl
