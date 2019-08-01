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

#ifndef SPATIUMGL_RENDERER_H
#define SPATIUMGL_RENDERER_H

#include <GL/glew.h> // GLuint

#include "RenderObject.hpp"
#include "Camera.hpp"
#include "spatiumglexport.h"

namespace spatiumgl {

class SPATIUMGL_EXPORT Renderer
{
public:
	Renderer(const RenderObject* renderObject)
		: m_renderObject(renderObject)
		, m_shaderProgram(0)
		, m_vao(0)
		, m_vbo(0)
		, m_valid(false)
	{}

	virtual ~Renderer() = default;

	bool isValid() const
	{
		return m_valid;
	}

	virtual void render(Camera* camera, float aspect) = 0;

protected:
	const RenderObject *m_renderObject;
	unsigned int m_shaderProgram;
	GLuint m_vao; // Vertex Array Object
	GLuint m_vbo; // Vertex Buffer Object
	bool m_valid;
};

} // namespace spatiumgl

#endif // SPATIUMGL_RENDERER_H