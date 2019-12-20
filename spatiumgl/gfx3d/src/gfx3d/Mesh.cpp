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

#include "spatiumgl/gfx3d/Mesh.hpp"

namespace spgl {
namespace gfx3d {

Mesh::Mesh(const std::vector<Vector3>&& vertices,
           const std::vector<Vector<size_t, 3>>&& triangles)
  : RenderObject()
  , m_vertices(std::move(vertices))
  , m_triangles(std::move(triangles))
{
}

Mesh Mesh::quad(const double radius)
{
  const std::vector<Vector3> vertices = {
    { -radius, -radius, 0 },
    { radius, -radius, 0 },
    { radius, radius, 0 },
    { -radius, radius, 0 },
  };

  const std::vector<Vector<size_t, 3>> triangles = { { 0, 1, 2 }, { 2, 3, 0 } };

  return { std::move(vertices), std::move(triangles) };
}

Mesh
Mesh::cube(const double radius)
{
  const std::vector<Vector3> vertices = { // front
                                          { -radius, -radius, radius },
                                          { radius, -radius, radius },
                                          { radius, radius, radius },
                                          { -radius, radius, radius },
                                          // back
                                          { -radius, -radius, -radius },
                                          { radius, -radius, -radius },
                                          { radius, radius, -radius },
                                          { -radius, radius, -radius }
  };

  const std::vector<Vector<size_t, 3>> triangles = { // front
                                                     { 0, 1, 2 },
                                                     { 2, 3, 0 },
                                                     // right
                                                     { 1, 5, 6 },
                                                     { 6, 2, 1 },
                                                     // back
                                                     { 7, 6, 5 },
                                                     { 5, 4, 7 },
                                                     // left
                                                     { 4, 0, 3 },
                                                     { 3, 7, 4 },
                                                     // bottom
                                                     { 4, 5, 1 },
                                                     { 1, 0, 4 },
                                                     // top
                                                     { 3, 2, 6 },
                                                     { 6, 7, 3 }
  };

  return { std::move(vertices), std::move(triangles) };
}


} // namespace gfx3d
} // namespace spgl
