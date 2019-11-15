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

#ifndef SPATIUMGL_GFX3D_OGLTRIANGLERENDERER_H
#define SPATIUMGL_GFX3D_OGLTRIANGLERENDERER_H

#include "OGLRenderer.hpp"
#include "spatiumglexport.hpp"

namespace spatiumgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OGLTriangleRenderer : public OGLRenderer
{
public:
  /// Constructor
  OGLTriangleRenderer();

  /// Destructor
  virtual ~OGLTriangleRenderer() override;

  void render(Camera* camera, double aspect) override;
};

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_OGLTRIANGLERENDERER_H
