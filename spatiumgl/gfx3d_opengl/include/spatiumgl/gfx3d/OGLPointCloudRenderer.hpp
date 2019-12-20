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

#ifndef SPATIUMGL_GFX3D_OGLPOINTCLOUDRENDERER_H
#define SPATIUMGL_GFX3D_OGLPOINTCLOUDRENDERER_H

#include "OGLRenderer.hpp"
#include "spatiumgl/gfx3d/PointCloudObject.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

struct SPATIUMGL_EXPORT PointCloudRenderOptions
{
  float pointSize = 1;
  bool pointScaleWorld = false;
  Vector3 color;
};

class SPATIUMGL_EXPORT OGLPointCloudRenderer : public OGLRenderer
{
public:
  /// Constructor
  ///
  /// \param[in] pointCloud Point cloud
  OGLPointCloudRenderer(const PointCloudObject* pointCloudObject, const PointCloudRenderOptions &renderOptions);

  /// Copy constructor. (deleted)
  OGLPointCloudRenderer(const OGLPointCloudRenderer& other) = delete;

  /// Copy assignment operator. (deleted)
  OGLPointCloudRenderer& operator=(const OGLPointCloudRenderer& other) = delete;

  /// Destructor
  virtual ~OGLPointCloudRenderer() override;

  /// Get point cloud render object.
  ///
  /// \return Point cloud render object
  const PointCloudObject* pointCloudObject() const;

  /// Render the point cloud.
  ///
  /// \param[in] camera Camera
  /// \param[in] size Render image size
  void render(Camera* camera, const Vector2i& size) override;

protected:
  PointCloudRenderOptions m_renderOptions;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_OGLPOINTCLOUDRENDERER_H
