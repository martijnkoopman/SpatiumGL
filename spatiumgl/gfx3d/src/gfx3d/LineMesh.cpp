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

#include "spatiumgl/gfx3d/LineMesh.hpp"

namespace spgl {
namespace gfx3d {

LineMesh::LineMesh(const std::vector<Vector3f>&& vertices,
                   const std::vector<Vector<unsigned int, 2>>&& lines,
                   const BoundingBox& bounds)
  : RenderObject(bounds)
  , m_vertices(std::move(vertices))
  , m_lines(std::move(lines))
{
  if (m_bounds.radii() == Vector3(0, 0, 0) && m_vertices.size() > 0) {
    // Compute bounds from vertices
    BoundingBox bounds(m_vertices[0].staticCast<double>(), { 0, 0, 0 });
    for (size_t i = 1; i < m_vertices.size(); i++) {
      bounds.include(m_vertices[i].staticCast<double>());
    }
    m_bounds = bounds;
  }
}

LineMesh
LineMesh::quad(const float radius)
{
  const std::vector<Vector3f> vertices = {
    { -radius, -radius, 0 },
    { radius, -radius, 0 },
    { radius, radius, 0 },
    { -radius, radius, 0 },
  };

  const std::vector<Vector<unsigned int, 2>> triangles = {
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }
  };

  return { std::move(vertices),
           std::move(triangles),
           { { 0, 0, 0 }, { radius, radius, 0 } } }; // bounds
}

LineMesh
LineMesh::cube(const float radius)
{
  const std::vector<Vector3f> vertices = { // top
                                           { -radius, -radius, radius },
                                           { radius, -radius, radius },
                                           { radius, radius, radius },
                                           { -radius, radius, radius },
                                           // bottom
                                           { -radius, -radius, -radius },
                                           { radius, -radius, -radius },
                                           { radius, radius, -radius },
                                           { -radius, radius, -radius }
  };

  const std::vector<Vector<unsigned int, 2>> lines = { // top
                                                       { 0, 1 },
                                                       { 1, 2 },
                                                       { 2, 3 },
                                                       { 3, 0 },
                                                       // bottom
                                                       { 4, 5 },
                                                       { 5, 6 },
                                                       { 6, 7 },
                                                       { 7, 4 },
                                                       // middle
                                                       { 0, 4 },
                                                       { 1, 5 },
                                                       { 2, 6 },
                                                       { 3, 7 }
  };

  return { std::move(vertices),
           std::move(lines),
           { { 0, 0, 0 }, { radius, radius, radius } } }; // bounds
}

LineMesh
LineMesh::grid(double spacing, const Vector2i& resolution)
{
  const size_t width = static_cast<size_t>(resolution.x());
  const size_t height = static_cast<size_t>(resolution.y());

  // Allocate memory for vertices
  const size_t vertexCount = (width + 1) * (height + 1);
  std::vector<Vector3f> vertices;
  vertices.reserve(vertexCount);

  // Allocate memory for lines
  const size_t lineCount = 2 * width * height + width + height;
  std::vector<Vector<unsigned int, 2>> lines;
  lines.reserve(lineCount);

  // Construct vertices + lines
  const Vector2f shift(spacing * width * 0.5, spacing * height * 0.5);
  for (size_t i = 0; i <= width; i++) {
    for (size_t j = 0; j <= height; j++) {
      // Vertex position
      const float x = i * spacing - shift.x();
      const float y = j * spacing - shift.y();
      vertices.emplace_back(x, y, 0);

      // Vertical line (2 vertex indices)
      if (j < height) {
        const size_t index = i * (height + 1) + j;
        lines.emplace_back(index, index + 1);
      }

      // Horizontal line (2 vertex indices)
      if (i < width) {
        const size_t index = i * (height + 1) + j;
        const size_t indexNext = index + (height + 1);
        lines.emplace_back(index, indexNext);
      }
    }
  }

  return { std::move(vertices),
           std::move(lines),
           { { 0, 0, 0 }, { shift.x(), shift.y(), 0 } } }; // bounds
}

} // namespace gfx3d
} // namespace spgl
