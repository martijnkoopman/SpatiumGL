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

#include "spatiumgl/gfx3d/SceneObject.hpp"

namespace spgl {
namespace gfx3d {

SceneObject::SceneObject()
  : m_transform()
{}

Transform&
SceneObject::transform()
{
  return m_transform;
}

const Transform&
SceneObject::transform() const
{
  return m_transform;
}

} // namespace gfx3d
} // namespace spgl
