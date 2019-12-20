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

#ifndef SPATIUMGL_GFX3D_OGLLINEMESHRENDERER_H
#define SPATIUMGL_GFX3D_OGLLINEMESHRENDERER_H

#include "OGLRenderer.hpp"
#include "spatiumgl/gfx3d/LineMesh.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OGLLineMeshRenderer : public OGLRenderer
{
public:
  /// Constructor.
  ///
  /// \param[in] lineMesh Line mesh
  OGLLineMeshRenderer(const LineMesh* lineMesh);

  /// Copy constructor. (deleted)
  OGLLineMeshRenderer(const OGLLineMeshRenderer& other) = delete;

  /// Copy assignment operator. (deleted)
  OGLLineMeshRenderer& operator=(const OGLLineMeshRenderer& other) = delete;

  /// Destructor
  virtual ~OGLLineMeshRenderer() override;

  /// Get the line mesh.
  ///
  /// \return Line mesh
  const LineMesh* lineMesh() const;

  /// Render the line mesh.
  ///
  /// \param[in] camera Camera
  /// \param[in] size Render image size
  void render(Camera* camera, const Vector2i& size) override;

protected:
  unsigned int m_ebo; // Element Buffer Object (GLuint)
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_OGLLINEMESHRENDERER_H
