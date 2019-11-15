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

#ifndef SPATIUMGL_GFX3D_ANIMATOR_H
#define SPATIUMGL_GFX3D_ANIMATOR_H

#include "RenderObject.hpp"
#include "spatiumglexport.hpp"

namespace spatiumgl {
namespace gfx3d {

class SPATIUMGL_EXPORT Animator
{
public:
  Animator(RenderObject* renderObject)
    : m_renderObject(renderObject)
  {}

  virtual ~Animator() = default;

  virtual void animate(double deltaTime) = 0;

protected:
  RenderObject* m_renderObject;
};

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_ANIMATION_H