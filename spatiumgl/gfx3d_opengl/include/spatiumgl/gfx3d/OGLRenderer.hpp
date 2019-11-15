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

#ifndef SPATIUMGL_GFX3D_OGLRENDERER_H
#define SPATIUMGL_GFX3D_OGLRENDERER_H

#include "spatiumgl/gfx3d/OGLShaderProgram.hpp"
#include "spatiumgl/gfx3d/Renderer.hpp"
#include "spatiumglexport.hpp"

namespace spatiumgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OGLRenderer : public Renderer
{
public:
  OGLRenderer(const RenderObject* renderObject)
    : Renderer(renderObject)
    , m_shaderProgram()
    , m_vao(0)
    , m_vbo(0)
  {}

protected:
  OGLShaderProgram m_shaderProgram;
  unsigned int m_vao; // Vertex Array Object (GLuint)
  unsigned int m_vbo; // Vertex Buffer Object (GLuint)
};

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_OGLRENDERER_H