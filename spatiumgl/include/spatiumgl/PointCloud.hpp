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

#ifndef SPATIUMGL_POINTCLOUD_H
#define SPATIUMGL_POINTCLOUD_H

#include <GL/glew.h>

#include "Camera.hpp"
#include "spatiumglexport.h"

//#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>

namespace spatiumgl {

class SPATIUMGL_EXPORT PointCloud
{
public:
	PointCloud(const std::vector<float>& positions, const std::vector<float>& colors = std::vector<float>());
	virtual ~PointCloud();

	bool isValid() const;
	void render(Camera* camera, float aspect);

protected:
	unsigned int m_shaderProgram;
	GLuint m_vao, m_vbo;
	bool m_valid;
	size_t m_pointCount;
};

} // namespace spatiumgl

#endif // SPATIUMGL_POINTCLOUD_H