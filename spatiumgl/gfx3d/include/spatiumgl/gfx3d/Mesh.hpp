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

#include "spatiumglexport.hpp"
#include "RenderObject.hpp"

#include <vector>

namespace spatiumgl {
	namespace gfx3d {

		/// \class Mesh
		/// \brief Triangluar mesh
		///
		/// ...
		class SPATIUMGL_EXPORT Mesh : public RenderObject
		{
		public:
			/// Constructor
			///
			/// \param[in] vertices Vertex positions
			/// \param[in] triangles Triangles. (Triplets of vertex indices)
			Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector<size_t, 3>> & triangles);

			/// Destructor
			virtual ~Mesh() = default;

			/// Get vertex count.
			///
			/// \return vertex count
			size_t vertexCount() const;

			/// Get triangle count.
			///
			/// \return triangle count
			size_t triangleCount() const;

			/// Get a vertex position.
			///
			/// \param[in] index Vertex index
			/// \return Vertex position (x,y,z)
			Vector3 vertex(size_t index) const;

			/// Get a triangle (triplet of vertex indices).
			///
			/// \param[in] index Triangle index
			/// \return Triangle vertex indices
			Vector<size_t, 3> triangle(size_t index) const;

			/// Get all vertex positions (by reference)
			///
			/// \return All vertex positions
			const std::vector<Vector3>& vertices() const;

			/// Get all triangles (triplets of vertex indices) (by reference)
			///
			/// \return All triangle vertex indices
			const std::vector<Vector<size_t, 3>> & triangles() const;

		protected:
			std::vector<Vector3> m_vertices;
			std::vector<Vector<size_t, 3>> m_triangles;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_MESH_H