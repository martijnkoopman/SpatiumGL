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

#include "spatiumgl/gfx3d/PointCloud.hpp"

namespace spatiumgl {

	PointCloud::PointCloud()
		: RenderObject()
		, m_positions()
		, m_colors()
		, m_normals()
	{}

	PointCloud::PointCloud(const std::vector<Vector3>& positions, 
							const std::vector<Vector3>& colors,
							const std::vector<Vector3>& normals
	)
		: RenderObject()
		, m_positions(positions)
		, m_colors(colors)
		, m_normals(normals)
	{}

	size_t PointCloud::pointCount() const
	{
		return m_positions.size();
	}

	bool PointCloud::addPoint(const Vector3& position)
	{
		m_positions.push_back(position);
		return false; // m_bounds.includePoint(point);
	}

	bool PointCloud::addPoint(const Vector3& position, const Vector3& color)
	{
		m_positions.push_back(position);
		m_colors.push_back(color);
		return false;// m_bounds.includePoint(point);
	}

	bool PointCloud::addPoint(const Vector3& position, const Vector3& color, const Vector3& normal)
	{
		m_positions.push_back(position);
		m_colors.push_back(color);
		m_normals.push_back(normal);
		return false;// m_bounds.includePoint(point);
	}

	// Positions

	const Vector3& PointCloud::position(size_t index) const
	{
		// Check bounds?
		return m_positions[index];
	}

	const std::vector<Vector3>& PointCloud::positions() const
	{
		return m_positions;
	}

	// Colors

	bool PointCloud::hasColors() const
	{
		return m_colors.size() > 0 && m_colors.size() == m_positions.size();
	}

	const Vector3& PointCloud::color(size_t index) const
	{
		// Check bounds?
		return m_colors[index];
	}

	const std::vector<Vector3>& PointCloud::colors() const
	{
		return m_colors;
	}

	// Normals

	bool PointCloud::hasNormals() const
	{
		return m_normals.size() > 0 && m_normals.size() == m_normals.size();
	}

	const Vector3& PointCloud::normal(size_t index) const
	{
		// Check bounds?
		return m_normals[index];
	}

	const std::vector<Vector3>& PointCloud::normals() const
	{
		return m_normals;
	}

} // namespace spatiumgl