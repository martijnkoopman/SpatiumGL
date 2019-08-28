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

#ifndef SPATIUMGL_OGLRENDERER_H
#define SPATIUMGL_OGLRENDERER_H

#include "spatiumglexport.hpp"
#include "spatiumgl/gfx3d/Renderer.hpp"
#include "spatiumgl/gfx3d/RenderObject.hpp"
#include "spatiumgl/gfx3d/Camera.hpp"

namespace spatiumgl {

class SPATIUMGL_EXPORT OGLRenderer : public Renderer
{
public:
	OGLRenderer(const RenderObject* renderObject)
		: Renderer(renderObject)
		, m_shaderProgram(0)
		, m_vao(0)
		, m_vbo(0)
	{}

protected:
	unsigned int m_shaderProgram;
	unsigned int m_vao; // Vertex Array Object  GLuint
	unsigned int m_vbo; // Vertex Buffer Object  GLuint
};

} // namespace spatiumgl

#endif // SPATIUMGL_OGLRENDERER_H