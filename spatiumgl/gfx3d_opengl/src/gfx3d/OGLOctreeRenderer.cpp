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

#include "OGLOctreeShaders.hpp"
#include "spatiumgl/gfx3d/LineMesh.hpp"
#include "spatiumgl/gfx3d/OGLOctreeRenderer.hpp"
#include "spatiumgl/gfx3d/PerspectiveCamera.hpp"

#include <array> // std::array
#include <iostream>
#include <queue> // std::queue
#include <string>
#include <utility> // std::pair

namespace spgl {
namespace gfx3d {

OGLOctreeRenderer::OGLOctreeRenderer(const OctreeObject* octObj)
  : OGLRenderer(octObj)
  , m_ebo(0)
  , m_instanceVbo(0)
{
  // Create shader program with vertex and fragment shader
  std::string vertexShaderSrc(octreeVertexShader);
  std::string fragmentShaderSrc(octreeFragmentShader);
  m_shaderProgram.setShaderSources(vertexShaderSrc, fragmentShaderSrc);

  // Validate shader program
  std::string errorMessage;
  if (!m_shaderProgram.validate(errorMessage)) {
    std::cerr << "[ERROR] fragment shader compilation: " << errorMessage
              << std::endl;
    m_valid = false;
    return;
  }

  // Create vertex array object (VAO)
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  LineMesh cube = LineMesh::cube(1);

  // Construct VBO for a single cube
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER,
               cube.vertices().size() * 3 * sizeof(float),
               cube.vertices().data(),
               GL_STATIC_DRAW);

  // Specificy vertex attributes (vertices)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Create, bind, allocate and fill element buffer object (EBO) and bind
  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               cube.lines().size() * 2 * sizeof(unsigned int),
               cube.lines().data(),
               GL_STATIC_DRAW);

  // Construct offsets and radii for cubes
  std::vector<Vector3f> offsets;
  std::vector<float> radii;
  const idx::Octree& octree = octObj->octree();

  // Traverse octree tree breadth-first (queue)
  // Push root node + bounds onto queue
  std::queue<std::pair<const idx::OctreeNode*, BoundingCube<double>>> queue;
  queue.push({ octree.root(), octree.bounds() });
  while (!queue.empty()) {
    // Pop node + bounds from queue
    const idx::OctreeNode* node = queue.front().first;
    const BoundingCube<double> bounds = queue.front().second;
    queue.pop();

    // Get offset and radius for instance of cube rendering
    offsets.push_back(bounds.center().staticCast<float>());
    radii.push_back(bounds.radius());

    // Push children on the queue (if any)
    for (size_t i = 0; i < 8; i++) {
      const idx::OctreeNode* child = node->child(i);
      if (child != nullptr) {
		// Compute bounds for child
        queue.push({ child, idx::Octree::computeChildBounds(bounds, i) });
	  }
	}
  }
  m_cubeCount = offsets.size();

  glGenBuffers(1, &m_instanceVbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_instanceVbo);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * 3 * offsets.size() +
                 radii.size() * sizeof(float),
               nullptr,
               GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER,
                  0,
                  sizeof(float) * 3 * offsets.size(),
                  (void*)offsets.data());
  glBufferSubData(GL_ARRAY_BUFFER,
                  sizeof(float) * 3 * offsets.size(),
                  sizeof(float) * radii.size(),
                  (void*)radii.data());

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
    1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        1,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(float),
                        (void*)(sizeof(float) * 3 * offsets.size()));
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // a attrib divisor of 1 means that attribute 2 will advance once
  // every instance (0 would mean once per vertex)
  glVertexAttribDivisor(1, 1);
  glVertexAttribDivisor(2, 1);

  // Unbind for now to prevent unintended overwriting
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // Element buffer object (EBO) is stored in VAO, do not unbind.
  glBindVertexArray(0);

  m_valid = true;
}

OGLOctreeRenderer::~OGLOctreeRenderer()
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
  glDeleteBuffers(1, &m_instanceVbo);
}

const OctreeObject*
OGLOctreeRenderer::octreeObject() const
{
  return static_cast<const OctreeObject*>(m_renderObject);
}

void
OGLOctreeRenderer::render(Camera* camera, const Vector2i& size)
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
  }

  // Bind vertex array object
  glBindVertexArray(m_vao);

  // Draw
  glDrawElementsInstanced(
    GL_LINES, 24, GL_UNSIGNED_INT, nullptr, m_cubeCount);

  // Unbind vertex array object
  glBindVertexArray(0);
}

} // namespace gfx3d
} // namespace spgl
