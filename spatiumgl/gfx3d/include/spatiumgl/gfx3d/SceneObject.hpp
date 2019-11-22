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

#ifndef SPATIUMGL_GFX3D_SCENEOBJECT_H
#define SPATIUMGL_GFX3D_SCENEOBJECT_H

#include "Transform.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

/// \class SceneObject
/// \brief Object in a 3D scene
///
/// A SceneObject is transformable in world space.
class SPATIUMGL_EXPORT SceneObject
{
public:
  /// Default constructor
  SceneObject();

  /// Get the transformation (by reference)
  ///
  /// \return transformation
  Transform& transform();

  /// Get the transformation (by const reference)
  ///
  /// \return transformation
  const Transform& transform() const;

protected:
  Transform m_transform;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_SCENEOBJECT_H