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

#ifndef SPATIUMGL_GFX3D_LINEMESH_H
#define SPATIUMGL_GFX3D_LINEMESH_H

#include "RenderObject.hpp"
#include "spatiumglexport.hpp"

#include <ostream>
#include <vector>

namespace spgl {
namespace gfx3d {

/// \class LineMesh
/// \brief Line mesh
class SPATIUMGL_EXPORT LineMesh : public RenderObject
{
public:
  /// Constructor
  ///
  /// \param[in] vertices Vertex positions
  /// \param[in] lines Lines. (Tuples of vertex indices)
  /// \param[in] bounds Boundaries (optional; computed if omitted)
  LineMesh(const std::vector<Vector3f>&& vertices,
           const std::vector<Vector<unsigned int, 2>>&& lines,
           const BoundingBox<double>& bounds = BoundingBox<double>());

  /// Get all vertex positions.
  ///
  /// \return All vertex positions
  const std::vector<Vector3f>& vertices() const { return m_vertices; }

  /// Get all lines (pairs of vertex indices)
  ///
  /// \return All line vertex indices
  const std::vector<Vector<unsigned int, 2>>& lines() const { return m_lines; }

  /// Construct quad line mesh.
  ///
  /// Has four lines.
  ///
  /// \param[in] radius Quad radius (default = 1)
  /// \return Quad line mesh
  static LineMesh quad(float radius = 1);

  /// Construct quad grid mesh.
  ///
  /// \param[in] radius Quad radius (default = 1)
  /// \return Grid line mesh
  static LineMesh grid(double spacing, const Vector2i &resolution);

  /// Construct cube mesh
  ///
  /// \param[in] radius Cube radius (default = 1)
  /// \return Cube mesh
  static LineMesh cube(float radius = 1);

  /// Output to ostream
  friend std::ostream& operator<<(std::ostream& os, const LineMesh& lineMesh)
  {
    os << "Vertices: [";
    for (const Vector3f vertex : lineMesh.m_vertices) {
      os << vertex;
    }
    os << "] Lines: [";
    for (const Vector<unsigned int, 2> line : lineMesh.m_lines) {
      os << line;
    }
    os << "]"
       << "\n";
    return os;
  }

protected:
  std::vector<Vector3f> m_vertices;
  std::vector<Vector<unsigned int, 2>> m_lines;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_LINEMESH_H
