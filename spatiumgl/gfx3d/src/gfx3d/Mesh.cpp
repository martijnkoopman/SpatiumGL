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

		/// \param[in] triangles Triangles. (Triplets of vertex indices)
		Mesh::Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector<size_t, 3>> & triangles)
			: RenderObject()
			, m_vertices(vertices)
			, m_triangles(triangles)
		{}

		size_t Mesh::vertexCount() const
		{
			return m_vertices.size();
		}

		size_t Mesh::triangleCount() const
		{
			return m_triangles.size();
		}

		Vector3 Mesh::vertex(size_t index) const
		{
			// Check bounds?
			return m_vertices[index];
		}

		/// \return Triangle vertex indices
		Vector<size_t, 3> Mesh::triangle(size_t index) const
		{
			// Check bounds?
			return m_triangles[index];
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