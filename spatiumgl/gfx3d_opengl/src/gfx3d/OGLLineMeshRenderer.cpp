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

#include "spatiumgl/gfx3d/OGLLineMeshRenderer.hpp"
#include "OGLLineMeshShaders.hpp"

#include <iostream>

namespace spgl {
namespace gfx3d {

OGLLineMeshRenderer::OGLLineMeshRenderer(const LineMesh* lineMesh)
  : OGLRenderer(lineMesh)
  , m_ebo(0)
{

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

  // Create and bind vertex array object (VAO) and bind
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // Create, bind, allocate and fill vertex buffer object (VBO) and bind
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER,
               lineMesh->vertices().size() * 3 * sizeof(float),
               lineMesh->vertices().data(),
               GL_STATIC_DRAW);

  // Create, bind, allocate and fill element buffer object (EBO) and bind
  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               lineMesh->lines().size() * 2 * sizeof(unsigned int),
               lineMesh->lines().data(),
               GL_STATIC_DRAW);

  // Specify strucutre of a single vertex attribute, and enable
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
  glEnableVertexAttribArray(0);

  // Unbind for now to prevent unintended overwriting
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // Element buffer object (EBO) is stored in VAO, do not unbind.
  glBindVertexArray(0);

  m_valid = true;
}

OGLLineMeshRenderer::~OGLLineMeshRenderer()
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
}

const LineMesh*
OGLLineMeshRenderer::lineMesh() const
{
  return static_cast<const LineMesh*>(m_renderObject);
}

void
OGLLineMeshRenderer::render(spgl::gfx3d::Camera* camera, const Vector2i& size)
{
  m_shaderProgram.use();

  {
    // Set model matrix
    const spgl::Matrix4 modelMatrix = m_renderObject->transform().matrix();
    int modelMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "model");
    const spgl::Matrix4f modelMatrixF = modelMatrix.staticCast<float>();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrixF.data());
  }

  {
    // Set view matrix
    const spgl::Matrix4 viewMatrix =
      camera->transform().matrix().inverse(); // MAY THROW EXCEPTION!
    int viewMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "view");
    const spgl::Matrix4f viewMatrixF = viewMatrix.staticCast<float>();
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrixF.data());
  }

  {
    // Set projection matrix
    const spgl::Matrix4 projectionMatrix =
      camera->projectionMatrix(static_cast<double>(size.x()) / size.y());
    int projectionMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "projection");
    const spgl::Matrix4f projectionMatrixF =
      projectionMatrix.staticCast<float>();
    glUniformMatrix4fv(
      projectionMatrixLoc, 1, GL_FALSE, projectionMatrixF.data());
  }

  // Bind vertex array object
  glBindVertexArray(m_vao);

  // Draw
  glDrawElements(
    GL_LINES, lineMesh()->lines().size() * 2, GL_UNSIGNED_INT, nullptr);

  // Unbind vertex array object
  glBindVertexArray(0);
}

} // namespace gfx3d
} // namespace spgl
