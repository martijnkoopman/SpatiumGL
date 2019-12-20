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

#ifndef SPATIUMGL_GFX3D_OGLOCTREERENDERER_H
#define SPATIUMGL_GFX3D_OGLOCTREERENDERER_H

#include "OGLRenderer.hpp"
#include "spatiumgl/gfx3d/OctreeObject.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OGLOctreeRenderer : public OGLRenderer
{
public:
  /// Constructor
  ///
  /// \param[in] octreeObject Octree object
  OGLOctreeRenderer(const OctreeObject* octreeObject);

  /// Copy constructor. (deleted)
  OGLOctreeRenderer(const OGLOctreeRenderer& other) = delete;

  /// Copy assignment operator. (deleted)
  OGLOctreeRenderer& operator=(const OGLOctreeRenderer& other) = delete;

  /// Destructor
  virtual ~OGLOctreeRenderer() override;

  /// Get octree render object.
  ///
  /// \return Octree render object
  const OctreeObject* octreeObject() const;

  /// Render the octree cloud.
  ///
  /// \param[in] camera Camera
  /// \param[in] size Render image size
  void render(Camera* camera, const Vector2i& size) override;

protected:
  size_t m_cubeCount;
  unsigned int m_ebo; // Element Buffer Object (GLuint)
  unsigned int m_instanceVbo; // Instance Vertex Buffer Object (GLuint)
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_OGLOCTREERENDERER_H
