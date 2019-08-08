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

#ifndef SPATIUMGL_MESH_H
#define SPATIUMGL_MESH_H

#include "spatiumglexport.hpp"
#include "RenderObject.hpp"

#include <glm/vec3.hpp>
#include <glm/gtx/std_based_type.hpp> // glm::tvec3<T>

#include <vector>

namespace spatiumgl {

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
	Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::tvec3<size_t>>& triangles);

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
	glm::vec3 vertex(size_t index) const;

	/// Get a triangle (triplet of vertex indices).
	///
	/// \param[in] index Triangle index
	/// \return Triangle vertex indices
	glm::tvec3<size_t> triangle(size_t index) const;

	/// Get all vertex positions (by reference)
	///
	/// \return All vertex positions
	const std::vector<glm::vec3>& vertices() const;

	/// Get all triangles (triplets of vertex indices) (by reference)
	///
	/// \return All triangle vertex indices
	const std::vector<glm::tvec3<size_t>>& triangles() const;

protected:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::tvec3<size_t>> m_triangles;
};

} // namespace spatiumgl

#endif // SPATIUMGL_MESH_H