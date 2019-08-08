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

#ifndef SPATIUMGL_POINTCLOUDRENDERER_H
#define SPATIUMGL_POINTCLOUDRENDERER_H

#include <GL/glew.h>

#include "spatiumglexport.hpp"
#include "Renderer.hpp"
#include "PointCloud.hpp"

namespace spatiumgl {

class SPATIUMGL_EXPORT PointCloudRenderer : public Renderer
{
public:
	/// Constructor
	///
	/// \param[in] pointCloud Point cloud
	PointCloudRenderer(const PointCloud *pointCloud);

	/// Destructor
	virtual ~PointCloudRenderer();

	/// Get the point cloud.
	///
	/// \return Point cloud
	const PointCloud* pointCloud() const;

	void render(Camera* camera, float aspect);
};

} // namespace spatiumgl

#endif // SPATIUMGL_POINTCLOUDRENDERER_H