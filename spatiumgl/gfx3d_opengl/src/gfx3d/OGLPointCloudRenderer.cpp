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

#include "OGLPointCloudShaders.hpp"
#include "spatiumgl/gfx3d/OGLPointCloudRenderer.hpp"
#include "spatiumgl/gfx3d/PerspectiveCamera.hpp"
#include "spatiumgl/Color.hpp"

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

  if (m_renderOptions.colorMethod == RGB &&
      pcObj->pointCloud().header().hasColors()) {
    // Color by RGB
    if (m_renderOptions.pointScaleWorld) {
      vertexShaderSrc = std::string(vertexShaderWorldSizeRGB);
    } else {
      vertexShaderSrc = std::string(vertexShaderScreenSizeRGB);
    }
    fragmentShaderSrc = std::string(fragmentShaderRGB);
  } else if (m_renderOptions.colorMethod == Scalar &&
             pcObj->pointCloud().header().hasScalars()) {
    // Color by scalar
    if (m_renderOptions.pointScaleWorld) {
      vertexShaderSrc = std::string(vertexShaderWorldSizeScalar);
    } else {
      vertexShaderSrc = std::string(vertexShaderScreenSizeScalar);
    }
    fragmentShaderSrc = std::string(fragmentShaderScalar);
  } else {
    // Fixed color
    if (m_renderOptions.pointScaleWorld) {
      vertexShaderSrc = std::string(vertexShaderWorldSizeNoColor);
    } else {
      vertexShaderSrc = std::string(vertexShaderScreenSizeNoColor);
    }
    fragmentShaderSrc = std::string(fragmentShaderNoColor);
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
  if (m_renderOptions.colorMethod == RGB &&
      pcObj->pointCloud().data().colors().size() == pointCount) {

    // Allocate vertex attributes buffer for points positions + colors
    glBufferData(GL_ARRAY_BUFFER, 2 * pointBufferSize, nullptr, GL_STATIC_DRAW);

    // Fill vertex attributes buffer with positions
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    pointBufferSize,
                    (void*)pcObj->pointCloud().data().positions().data());
    // Fill vertex attributes buffer with colors
    glBufferSubData(GL_ARRAY_BUFFER,
                    pointBufferSize,
                    pointBufferSize,
                    (void*)pcObj->pointCloud().data().colors().data());

    // Specify vertex attribute format for point position, and enable
    glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    // Specify vertex attribute format for point color, and enable
    glVertexAttribPointer(
      1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(pointBufferSize));
    glEnableVertexAttribArray(1);
  } else if (m_renderOptions.colorMethod == Scalar &&
             pcObj->pointCloud().data().scalars().values().size() ==
               pointCount) {

    const size_t scalarsBufferSize = pointCount * sizeof(float);

    // Allocate vertex attributes buffer for point positions + scalars
    glBufferData(GL_ARRAY_BUFFER,
                 pointBufferSize + scalarsBufferSize,
                 nullptr,
                 GL_STATIC_DRAW);

    // Fill vertex attributes buffer with positions
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    pointBufferSize,
                    (void*)pcObj->pointCloud().data().positions().data());
    // Fill vertex attributes buffer with scalars
    glBufferSubData(
      GL_ARRAY_BUFFER,
      pointBufferSize,
      scalarsBufferSize,
      (void*)pcObj->pointCloud().data().scalars().values().data());

    // Specify vertex attribute format for point position, and enable
    glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    // Specify vertex attribute format for point color, and enable
    glVertexAttribPointer(
      1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)(pointBufferSize));
    glEnableVertexAttribArray(1);

  } else {
    // Allocate vertex attributes buffer for point positions
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

  if (m_renderOptions.pointScaleWorld) {
    glEnable(GL_PROGRAM_POINT_SIZE);
  }

  m_valid = true;
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

    if (m_renderOptions.pointScaleWorld) {

      const PerspectiveCamera* perspectiveCamera =
        dynamic_cast<PerspectiveCamera*>(camera);

      if (perspectiveCamera != nullptr) {
        float distanceScreen = size.y() * projectionMatrix[1][1]; // 1/tan(a/2)
        int distanceScreenLoc = glGetUniformLocation(
          m_shaderProgram.shaderProgamId(), "distanceScreen");
        glUniform1f(distanceScreenLoc, distanceScreen);
      }

      {
        int pointSizeLoc =
          glGetUniformLocation(m_shaderProgram.shaderProgamId(), "pointSize");
        glUniform1f(pointSizeLoc, m_renderOptions.pointSize);
      }
    } else {
      glPointSize(m_renderOptions.pointSize);
    }
  }

  if (m_renderOptions.colorMethod == Scalar) {
	// Set color ramp range
    int colorRampRangeLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "colorramp_range");
    std::array<float, 2> range =
      pointCloudObject()->pointCloud().data().scalars().range();
    glUniform1fv(colorRampRangeLoc, 2, range.data());

	// Set color ramp colors
    ColorRampT<float> ramp = ColorRampT<float>::spectral(range[0], range[1]);
    int colorRampColorsLoc =
      glGetUniformLocation(m_shaderProgram.shaderProgamId(), "colorramp_colors");
    glUniform4fv(colorRampColorsLoc, 32, ramp.toArray<32>().data()->data()); // Number of colors must match shader
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
