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

#ifndef SPATIUMGL_GFX3D_MESH_H
#define SPATIUMGL_GFX3D_MESH_H

#include "RenderObject.hpp"
#include "spatiumglexport.hpp"

#include <ostream>
#include <vector>

namespace spgl {
namespace gfx3d {

/// \class Mesh
/// \brief Triangluar mesh
///
/// ...
class SPATIUMGL_EXPORT Mesh : public RenderObject
{
public:
  /// Constructor.
  ///
  /// Vertices and triangles are moved.
  ///
  /// \param[in] vetices. Vertices, coordinates.
  /// \param[in] triangles Triangles, triplets of vertex indices.
  Mesh(const std::vector<Vector3>&& vertices,
       const std::vector<Vector<size_t, 3>>&& triangles);

  /// Get all vertex positions.
  ///
  /// \return All vertex positions
  const std::vector<Vector3>& vertices() const { return m_vertices; }

  /// Get all triangles (triplets of vertex indices)
  ///
  /// \return All triangle vertex indices
  const std::vector<Vector<size_t, 3>>& triangles() const
  {
    return m_triangles;
  }

  /// Construct quad mesh.
  ///
  /// Has two triangles.
  ///
  /// \param[in] radius Quad radius (default = 1)
  /// \return Quad mesh
  static Mesh quad(double radius = 1);

  /// Construct cube mesh
  ///
  /// \param[in] radius Cube radius (default = 1)
  /// \return Cube mesh
  static Mesh cube(double radius = 1);

  /// Output to ostream
  friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh)
  {
    os << "Vertices: [";
    for (const Vector3 vertex : mesh.m_vertices) {
      os << vertex;
    }
    os << "] Triangles: [";
    for (const Vector<size_t, 3> triangle : mesh.m_triangles) {
      os << triangle;
    }
    os << "]"
       << "\n";
    return os;
  }

protected:
  std::vector<Vector3> m_vertices;
  std::vector<Vector<size_t, 3>> m_triangles;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_MESH_H
