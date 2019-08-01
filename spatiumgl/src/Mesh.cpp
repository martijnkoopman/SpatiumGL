#include "spatiumgl/Mesh.hpp"

namespace spatiumgl {

	/// \param[in] triangles Triangles. (Triplets of vertex indices)
	Mesh::Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::tvec3<size_t>> &triangles)
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

	glm::vec3 Mesh::vertex(size_t index) const
	{
		// Check bounds?
		return m_vertices[index];
	}

	/// \return Triangle vertex indices
	glm::tvec3<size_t> Mesh::triangle(size_t index) const
	{
		// Check bounds?
		return m_triangles[index];
	}

	const std::vector<glm::vec3>& Mesh::vertices() const
	{
		return m_vertices;
	}

	const std::vector<glm::tvec3<size_t>>& Mesh::triangles() const
	{
		return m_triangles;
	}

} // namespace spatiumgl