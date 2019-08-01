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

#ifndef SPATIUMGL_POINTCLOUD_H
#define SPATIUMGL_POINTCLOUD_H

#include "RenderObject.hpp"
#include "spatiumglexport.h"
#include <glm/vec3.hpp>
#include <vector>

namespace spatiumgl {

/// \class PointCloud
/// \brief Point cloud with optional colors
class SPATIUMGL_EXPORT PointCloud : public RenderObject
{
public:
	
	/// Constructor
	///
	/// \param[in] positions Point positions
	/// \param[in] colors Point colors (r,g,b)
	PointCloud(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& colors = std::vector<glm::vec3>());

	/// Destructor
	virtual ~PointCloud() = default;

	/// Get point count.
	///
	/// \return Point count
	size_t pointCount() const;

	/// Get a point position.
	///
	/// \param[in] index Point index
	/// \return Point position (x,y,z)
	glm::vec3 position(size_t index) const;

	/// Get all point positions (by reference)
	///
	/// \return All point positions
	const std::vector<glm::vec3>& positions() const;

	/// Has color?
	///
	/// True if colors are present, false otherwise
	bool hasColors() const;

	/// Get a point color.
	///
	/// \param[in] index Point index
	/// \return Point color (r,g,b)
	glm::vec3 color(size_t index) const;

	/// Get all point colors (by reference)
	///
	/// \return All point positions
	const std::vector<glm::vec3>& colors() const;

protected:
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec3> m_colors;

	// TODO: Create class Scalars
};

/*
class Scalars
{
public:
	enum ScalarType
	{
		TYPE_CHAR,
		TYPE_SHORT,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_DOUBLE
	};

	/// Constructor
	///
	/// \param[in] type Scalar type
	/// \param[in] dimension Scalar dimension
	Scalars(ScalarType type, size_t components = 1)
		: m_scalarType(type)
		, m_scalarDimension(dimension)
	{

	}

	/// Get scalar count.
	///
	/// \return Scalar count
	size_t count() const
	{
		return sizeof(m_data) / scalarSize();
	}

	/// Get size of a single scalar in bytes.
	///
	/// \return Scalar size
	size_t scalarSize()
	{
		switch (m_scalarType)
		{
		case Scalars::TYPE_CHAR:
			return sizeof(char);
		case Scalars::TYPE_SHORT:
			return sizeof(short);
		case Scalars::TYPE_INT:
			return sizeof(int);
		case Scalars::TYPE_FLOAT:
			return sizeof(float);
		case Scalars::TYPE_DOUBLE:
			return sizeof(double);
		default:
			return sizeof(char);
		}
	}

	/// Get a scalar as double.
	///
	/// Only use this function if the scalars have a dimension of 1.
	///
	/// \param[in] index Index of scalar
	/// \return Scalar value as double
	double scalarAsDouble(size_t scalarCndex) const
	{
		return static_cast<double>(*(m_data + index * scalarSize(m_scalarType)));
	}

	std::array<double, m_dimension> scalarsAsDoubleArray(size_t

protected:
	const ScalarType m_scalarType;
	const size_t m_scalarComponentCount;
	unsigned char* m_data; // TODO: std::unique_ptr
};
*/

} // namespace spatiumgl

#endif // SPATIUMGL_POINTCLOUD_H