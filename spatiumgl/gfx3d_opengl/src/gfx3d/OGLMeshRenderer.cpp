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

#include "spatiumgl/gfx3d/OGLMeshRenderer.hpp"

#include <iostream>
#include <string>

namespace spatiumgl {
namespace gfx3d {

OGLMeshRenderer::OGLMeshRenderer(const Mesh* mesh, const Material& material)
  : OGLRenderer(mesh)
  , m_ebo(0)
  , m_material(material)
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

  std::string fragmentShaderSrc =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 meshColor;"
    "void main()\n"
    "{\n"
    "FragColor = meshColor;\n" // vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

  const size_t vertexCount = mesh->vertices().size();
  std::vector<Vector3f> verticesFloat(vertexCount);
  for (size_t i = 0; i < vertexCount; i++) {
    verticesFloat[i] = mesh->vertices()[i].staticCast<float>();
  }

  const size_t triangleCount = mesh->triangles().size();
  std::vector<Vector<unsigned int, 3>> indicesInt(triangleCount);
  for (size_t i = 0; i < triangleCount; i++) {
    indicesInt[i] = mesh->triangles()[i].staticCast<unsigned int>();
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
               triangleCount * 3 * sizeof(unsigned int),
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

  glCullFace(GL_FRONT_AND_BACK);
}

OGLMeshRenderer::~OGLMeshRenderer()
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
}

const Mesh*
OGLMeshRenderer::mesh() const
{
  return static_cast<const Mesh*>(m_renderObject);
}

void
OGLMeshRenderer::render(spatiumgl::gfx3d::Camera* camera, double aspect)
{
  m_shaderProgram.use();

  {
    // Set model matrix
    const spatiumgl::Matrix4 modelMatrix = m_renderObject->transform().matrix();
    int modelMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "model");
    const spatiumgl::Matrix4f modelMatrixF = modelMatrix.staticCast<float>();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrixF.data());
  }

  {
    // Set view matrix
    const spatiumgl::Matrix4 viewMatrix =
      camera->transform().matrix().inverse(); // MAY THROW EXCEPTION!
    int viewMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "view");
    const spatiumgl::Matrix4f viewMatrixF = viewMatrix.staticCast<float>();
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrixF.data());
  }

  {
    // Set projection matrix
    const spatiumgl::Matrix4 projectionMatrix =
      camera->projectionMatrix(aspect);
    int projectionMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "projection");
    const spatiumgl::Matrix4f projectionMatrixF =
      projectionMatrix.staticCast<float>();
    glUniformMatrix4fv(
      projectionMatrixLoc, 1, GL_FALSE, projectionMatrixF.data());
  }

  {
    int meshColorLocation =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "meshColor");
    glUniform4f(meshColorLocation,
                (float)m_material.color()[0],
                (float)m_material.color()[1],
                (float)m_material.color()[2],
                (float)m_material.color()[3]);
  }

  // Bind vertex array object
  glBindVertexArray(m_vao);

  // Draw
  glDrawElements(
    GL_TRIANGLES, mesh()->triangles().size() * 3, GL_UNSIGNED_INT, nullptr);

  // Unbind vertex array object
  glBindVertexArray(0);
}

} // namespace gfx3d
} // namespace spatiumgl
