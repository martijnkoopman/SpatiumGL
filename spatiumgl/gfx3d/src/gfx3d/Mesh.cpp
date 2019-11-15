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

namespace spatiumgl {
	namespace gfx3d {

		/// Constructor
		///
		/// \param[in] vetices. Vertices, coordinates.
		/// \param[in] triangles Triangles, triplets of vertex indices.
		Mesh::Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector<size_t, 3>> & triangles)
			: RenderObject()
			, m_vertices(vertices)
			, m_triangles(triangles)
    {
      /// \todo std::move semantics for vectors
    }

		const std::vector<Vector3>& Mesh::vertices() const
		{
			return m_vertices;
		}

		const std::vector<Vector<size_t, 3>> & Mesh::triangles() const
		{
			return m_triangles;
		}

	} // namespace gfx3d
} // namespace spatiumgl
