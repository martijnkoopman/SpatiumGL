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

#include "spatiumgl/gfx3d/OGLGridRenderer.hpp"

#include <iostream>
#include <string>

namespace spgl {
namespace gfx3d {

OGLGridRenderer::OGLGridRenderer(const Grid* grid)
  : OGLRenderer(grid)
  , m_ebo(0)
{
  std::string vertexShaderSrc =
    "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);\n"
    "}";

  std::string fragmentShaderSrc = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "uniform vec4 gridColor;"
                                  "void main()\n"
                                  "{\n"
                                  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                  "}";

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

  const size_t radiusX = grid->radiusX();
  const size_t radiusY = grid->radiusY();

  // Construct vertices
  const size_t vertexCount = (2 * radiusX + 1) * (2 * radiusY + 1);
  std::vector<Vector3f> verticesFloat(vertexCount);
  size_t vertexIndex = 0;
  for (size_t i = 0; i < 2 * radiusX + 1; i++) {
    float x = static_cast<float>(i * grid->spacingX() -
                                 grid->radiusX() * grid->spacingX());

    for (size_t j = 0; j < 2 * radiusY + 1; j++) {
      float y = static_cast<float>(j * grid->spacingY() -
                                   grid->radiusY() * grid->spacingY());

      verticesFloat[vertexIndex] = Vector3f(x, y, 0);
      vertexIndex++;
    }
  }

  // Construct lines
  const size_t lineCount =
    ((2 * radiusY) * (2 * radiusX + 1)) + ((2 * radiusX) * (2 * radiusY + 1));
  std::vector<Vector<unsigned int, 2>> indicesInt(lineCount);
  size_t lineIndex = 0;

  // Lines along y axis (vertical)
  for (size_t i = 0; i < 2 * radiusX + 1; i++) {
    for (size_t j = 0; j < 2 * radiusY; j++) {
      size_t index = i * (radiusY * 2 + 1) + j;

      // Line along y axis
      indicesInt[lineIndex] = { static_cast<unsigned int>(index),
                                static_cast<unsigned int>(index + 1) };
      lineIndex++;
    }
  }

  // Line along x axis (horizontal)
  for (size_t i = 0; i < 2 * radiusX; i++) {
    for (size_t j = 0; j < 2 * radiusY + 1; j++) {
      size_t index = i * (radiusY * 2 + 1) + j;

      indicesInt[lineIndex] = { static_cast<unsigned int>(index),
                                static_cast<unsigned int>(index +
                                                          (radiusY * 2 + 1)) };
      lineIndex++;
    }
  }

  // Create and bind vertex array object (VAO) and bind
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // Create, bind, allocate and fill vertex buffer object (VBO) and bind
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER,
               vertexCount * 3 * sizeof(float),
               verticesFloat.data(),
               GL_STATIC_DRAW);

  // Create, bind, allocate and fill element buffer object (EBO) and bind
  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               lineCount * 2 * sizeof(unsigned int),
               indicesInt.data(),
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

OGLGridRenderer::~OGLGridRenderer()
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
}

const Grid*
OGLGridRenderer::grid() const
{
  return static_cast<const Grid*>(m_renderObject);
}

void
OGLGridRenderer::render(spgl::gfx3d::Camera* camera, const Vector2i& size)
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

  const size_t lineCount =
    ((2 * grid()->radiusY()) * (2 * grid()->radiusX() + 1)) +
    ((2 * grid()->radiusX()) * (2 * grid()->radiusY() + 1));

  // Draw
  glDrawElements(GL_LINES, lineCount * 2, GL_UNSIGNED_INT, nullptr);

  // Unbind vertex array object
  glBindVertexArray(0);
}

} // namespace gfx3d
} // namespace spgl
