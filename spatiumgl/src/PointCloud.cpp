#include "spatiumgl/PointCloud.hpp"

namespace spatiumgl {

	PointCloud::PointCloud(const std::vector<glm::vec3> &positions, const std::vector<glm::vec3> &colors)
		: RenderObject()
		, m_positions(positions)
		, m_colors(colors)
  {}

	size_t PointCloud::pointCount() const
	{
		return m_positions.size();
	}

	glm::vec3 PointCloud::position(size_t index) const
	{
		// Check bounds?
		return m_positions[index];
	}

	const std::vector<glm::vec3>& PointCloud::positions() const
	{
		return m_positions;
	}

	bool PointCloud::hasColors() const
	{
		return m_colors.size() > 0 && m_colors.size() == m_positions.size();
	}

	glm::vec3 PointCloud::color(size_t index) const
	{
		// Check bounds?
		return m_colors[index];
	}

	const std::vector<glm::vec3>& PointCloud::colors() const
	{
		return m_colors;
	}


} // namespace spatiumgl