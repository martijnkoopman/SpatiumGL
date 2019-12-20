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

#include "spatiumgl/gfx3d/OGLPointCloudRenderer.hpp"
#include "spatiumgl/gfx3d/PerspectiveCamera.hpp"
#include "OGLPointCloudShaders.hpp"

#include <iostream>
#include <string>

namespace spgl {
namespace gfx3d {

OGLPointCloudRenderer::OGLPointCloudRenderer(
  const PointCloudObject* pcObj,
  const PointCloudRenderOptions& renderOptions)
  : OGLRenderer(pcObj)
  , m_renderOptions(renderOptions)
{
  std::string vertexShaderSrc;
  std::string fragmentShaderSrc;
  if (pcObj->pointCloud().header().hasColors()) {
    vertexShaderSrc = std::string(vertexShaderColorFixedSize);
    fragmentShaderSrc = std::string(fragmentShaderColor);
  } else {
    // Shader
    vertexShaderSrc = vertexShaderNoPointSize;
    fragmentShaderSrc = fragmentShaderSingleColor;
  }

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

  // Create vertex array object (VAO) and bind
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // Create vertex buffer object (VBO) and bind
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  const size_t pointCount = pcObj->pointCloud().data().positions().size();
  // Allocate vertex attributes buffer
  const size_t pointBufferSize = pointCount * sizeof(float) * 3;
  if (pcObj->pointCloud().data().colors().size() == pointCount) {

    // Allocate vertex attributes buffer for points + colors
    glBufferData(GL_ARRAY_BUFFER, 2 * pointBufferSize, nullptr, GL_STATIC_DRAW);

    // Fill vertex attributes with positions and colors
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    pointBufferSize,
                    (void*)pcObj->pointCloud().data().positions().data());
    glBufferSubData(GL_ARRAY_BUFFER,
                    pointBufferSize,
                    pointBufferSize,
                    (void*)pcObj->pointCloud().data().colors().data());

    // Specify strucutre of a single vertex attribute, and enable
    glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr); // positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          3 * sizeof(float),
                          (void*)(pointBufferSize)); // colors
    glEnableVertexAttribArray(1);
  } else {
    // Allocate vertex attributes buffer for points
    glBufferData(GL_ARRAY_BUFFER,
                 pointBufferSize,
                 pcObj->pointCloud().data().positions().data(),
                 GL_STATIC_DRAW);

    // Specify strucutre of a single vertex attribute, and enable
    glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
  }

  // Unbind for now to prevent unintended overwriting
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  m_valid = true;

  glEnable(GL_PROGRAM_POINT_SIZE);
}

OGLPointCloudRenderer::~OGLPointCloudRenderer()
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
}

const PointCloudObject*
OGLPointCloudRenderer::pointCloudObject() const
{
  return static_cast<const PointCloudObject*>(m_renderObject);
}

void
OGLPointCloudRenderer::render(Camera* camera, const Vector2i& size)
{
  m_shaderProgram.use();

  {
    // Set model matrix
    const Matrix4 modelMatrix = m_renderObject->transform().matrix();
    int modelMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "model");
    const Matrix4f modelMatrixF = modelMatrix.staticCast<float>();
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrixF.data());
  }

  {
    // Set view matrix
    const Matrix4 viewMatrix =
      camera->transform().matrix().inverse(); // MAY THROW EXCEPTION!
    int viewMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "view");
    const Matrix4f viewMatrixF = viewMatrix.staticCast<float>();
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrixF.data());
  }

  {
    // Set projection matrix
    const Matrix4 projectionMatrix =
      camera->projectionMatrix(static_cast<double>(size.x()) / size.y());
    int projectionMatrixLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "projection");
    const Matrix4f projectionMatrixF = projectionMatrix.staticCast<float>();
    glUniformMatrix4fv(
      projectionMatrixLoc, 1, GL_FALSE, projectionMatrixF.data());

    const PerspectiveCamera* perspectiveCamera =
      dynamic_cast<PerspectiveCamera*>(camera);
    if (perspectiveCamera != nullptr) {
      float distanceScreen = size.y() * projectionMatrix[1][1]; // 1/tan(a/2)
      int distanceScreenLoc = glGetUniformLocation(
        m_shaderProgram.shaderProgamId(), "distanceScreen");
      glUniform1f(distanceScreenLoc, distanceScreen);
    }
  }

  {
    //float pointSize = 0.20;
    int pointSizeLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "pointSize");
    glUniform1f(pointSizeLoc, m_renderOptions.pointSize);
  }

  // Bind vertex array object
  glBindVertexArray(m_vao);

  // Draw
  glDrawArrays(
    GL_POINTS, 0, pointCloudObject()->pointCloud().header().pointCount());

  // Unbind vertex array object
  glBindVertexArray(0);
}

} // namespace gfx3d
} // namespace spgl
