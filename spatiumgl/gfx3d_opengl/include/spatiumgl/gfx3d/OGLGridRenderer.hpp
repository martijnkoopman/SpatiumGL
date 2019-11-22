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

#ifndef SPATIUMGL_GFX3D_OGLGRIDRENDERER_H
#define SPATIUMGL_GFX3D_OGLGRIDRENDERER_H

#include "OGLRenderer.hpp"
#include "spatiumgl/gfx3d/Grid.hpp"
#include "spatiumgl/gfx3d/Material.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OGLGridRenderer : public OGLRenderer
{
public:
  /// Constructor
  ///
  /// \param[in] grid Grid
  OGLGridRenderer(const Grid* grid);

  /// Destructor
  virtual ~OGLGridRenderer() override;

  /// Get the mesh.
  ///
  /// \returnMesh
  const Grid* grid() const;

  void render(Camera* camera, double aspect) override;

protected:
  unsigned int m_ebo; // Element Buffer Object (GLuint)
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_OGLGRIDRENDERER_H
