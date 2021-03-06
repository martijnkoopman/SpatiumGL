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

#ifndef SPATIUMGL_GFX3D_OGLMESHRENDERER_H
#define SPATIUMGL_GFX3D_OGLMESHRENDERER_H

#include "OGLRenderer.hpp"
#include "spatiumgl/gfx3d/Material.hpp"
#include "spatiumgl/gfx3d/Mesh.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OGLMeshRenderer : public OGLRenderer
{
public:
  /// Constructor
  ///
  /// \param[in] mesh Mesh
  OGLMeshRenderer(const Mesh* mesh, const Material& material);

  /// Copy constructor. (deleted)
  OGLMeshRenderer(const OGLMeshRenderer& other) = delete;

  /// Copy assignment operator. (deleted)
  OGLMeshRenderer& operator=(const OGLMeshRenderer& other) = delete;

  /// Destructor
  virtual ~OGLMeshRenderer() override;

  /// Get the mesh.
  ///
  /// \return Mesh
  const Mesh* mesh() const;

  /// Render the mesh.
  ///
  /// \param[in] camera Camera
  /// \param[in] size Render image size
  void render(Camera* camera, const Vector2i& size) override;

protected:
  unsigned int m_ebo; // Element Buffer Object (GLuint)
  Material m_material;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_OGLMESHRENDERER_H
