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
#include <ostream>

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

			/// Get all vertex positions (by reference)
			///
			/// \return All vertex positions
			const std::vector<Vector3>& vertices() const;

			/// Get all triangles (triplets of vertex indices) (by reference)
			///
			/// \return All triangle vertex indices
			const std::vector<Vector<size_t, 3>> & triangles() const;

			/// Construct quad mesh
			///
			/// \param[in] radius Quad radius (default = 1)
			/// \return Quad mesh
			static Mesh quad(double radius = 1)
			{
				const std::vector<Vector3> vertices = {
					{ -radius, -radius,  0 },
					{  radius, -radius,  0 },
					{  radius,  radius,  0 },
					{ -radius,  radius,  0 },
				};

				const std::vector<Vector<size_t, 3>> triangles = {
					{ 0, 1, 2 },
					{ 2, 3, 0 }
				};

				return Mesh(vertices, triangles);
			}

			/// Construct far quad mesh (debugging only)
			///
			/// \param[in] radius Quad radius (default = 1)
			/// \return Quad mesh
			static Mesh quadFar(double radius = 1)
			{
				const std::vector<Vector3> vertices = {
					{ -radius, -radius,  -0.5 },
					{  radius, -radius,  -0.5 },
					{  radius,  radius,  -0.5 },
					{ -radius,  radius,  -0.5 },
				};

				const std::vector<Vector<size_t, 3>> triangles = {
					{ 0, 1, 2 },
					{ 2, 3, 0 }
				};

				return Mesh(vertices, triangles);
			}

			/// Construct cube mesh
			///
			/// \param[in] radius Cube radius (default = 1)
			/// \return Cube mesh
			static Mesh cube(double radius = 1)
			{
				const std::vector<Vector3> vertices = {
					// front
					{ -radius, -radius,  radius },
					{  radius, -radius,  radius },
					{  radius,  radius,  radius },
					{ -radius,  radius,  radius },
					// back
					{ -radius, -radius, -radius },
					{ radius, -radius, -radius },
					{ radius,  radius, -radius },
					{ -radius,  radius, -radius }
				};

				const std::vector<Vector<size_t, 3>> triangles = {
					// front
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

				return Mesh(vertices, triangles);
			}

		/// Output to ostream
		friend std::ostream& operator<<(std::ostream& os, const Mesh &mesh)
		{
			os << "Vertices: [";
			for (const Vector3 vertex : mesh.m_vertices)
			{
				os << vertex;
			}
			os << "] Triangles: [";
			for (const Vector<size_t, 3> triangle : mesh.m_triangles)
			{
				os << triangle;
			}
			os << "]" << "\n";
			return os;
		}

		protected:
			std::vector<Vector3> m_vertices;
			std::vector<Vector<size_t, 3>> m_triangles;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_MESH_H