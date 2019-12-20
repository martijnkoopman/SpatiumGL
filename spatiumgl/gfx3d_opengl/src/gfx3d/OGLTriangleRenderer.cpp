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

#include <GL/glew.h>

#include "spatiumgl/gfx3d/OGLTriangleRenderer.hpp"

#include <iostream>

namespace spgl {
namespace gfx3d {

OGLTriangleRenderer::OGLTriangleRenderer()
  : OGLRenderer(nullptr)
{
  // Shader
  std::string vertexShaderSrc(
    "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view * vec4(aPos, 1.0);\n"
    "}");

  std::string fragmentShaderSrc("#version 330 core\n"
                                "out vec4 FragColor;\n"
                                "void main()\n"
                                "{\n"
                                "FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
                                "}");

  // Create shader program with vertex and fragment shader
  m_shaderProgram.setShaderSources(vertexShaderSrc, fragmentShaderSrc);

  // Validate shader program
  std::string errorMessage;
  if (!m_shaderProgram.validate(errorMessage)) {
    std::cerr << "[ERROR] fragment shader compilation: " << errorMessage
              << std::endl;
    m_valid = false;
    return;
  }

  // Vertices
  float vertices[] = {
    -0.5, -0.5, -1, 0.5, -0.5, -1, 0.0, 0.5, -1, 0.0, 0.0, -1
  };

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
  glEnableVertexAttribArray(0);

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  m_valid = true;
}

OGLTriangleRenderer::~OGLTriangleRenderer()
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
}

void
OGLTriangleRenderer::render(spgl::gfx3d::Camera* camera, const Vector2i& size)
{
  m_shaderProgram.use();

  // Set view matrix
  const spgl::Matrix4 viewMatrix =
    camera->transform().matrix().inverse(); // MAY THROW EXCEPTION!
  int viewMatrixLoc =
    glGetUniformLocation(m_shaderProgram.shaderProgamId(), "view");
  const spgl::Matrix4f viewMatrixF = viewMatrix.staticCast<float>();
  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrixF.data());

  // Set projection matrix
  const spgl::Matrix4 projectionMatrix =
    camera->projectionMatrix(static_cast<double>(size.x()) / size.y());
  int projectionMatrixLoc =
    glGetUniformLocation(m_shaderProgram.shaderProgamId(), "projection");
  const spgl::Matrix4f projectionMatrixF = projectionMatrix.staticCast<float>();
  glUniformMatrix4fv(
    projectionMatrixLoc, 1, GL_FALSE, projectionMatrixF.data());

  // Bind vertex array object
  glBindVertexArray(m_vao);

  // Draw
  glDrawArrays(GL_POINTS, 0, 4);
}

} // namespace gfx3d
} // namespace spgl
