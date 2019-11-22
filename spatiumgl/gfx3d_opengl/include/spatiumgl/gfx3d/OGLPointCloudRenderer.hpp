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

namespace spatiumgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OGLPointCloudRenderer : public OGLRenderer
{
public:
  /// Constructor
  ///
  /// \param[in] pointCloud Point cloud
  OGLPointCloudRenderer(const PointCloudObject* pointCloudObject);

  /// Destructor
  virtual ~OGLPointCloudRenderer() override;

  /// Get point cloud render object.
  ///
  /// \return Point cloud render object
  const PointCloudObject* pointCloudObject() const;

  void render(Camera* camera, double aspect) override;
};

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_OGLPOINTCLOUDRENDERER_H
