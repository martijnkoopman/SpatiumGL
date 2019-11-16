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

#ifndef SPATIUMGL_GFX3D_POINTCLOUD_H
#define SPATIUMGL_GFX3D_POINTCLOUD_H

#include "RenderObject.hpp"
#include "spatiumgl/Vector.hpp"
#include "spatiumglexport.hpp"

#include <vector>

namespace spatiumgl {
namespace gfx3d {

/// \class PointCloud
/// \brief Point cloud with optional colors
///
/// This is a container for points and optionally scalars (colors, normals)
class SPATIUMGL_EXPORT PointCloud : public RenderObject
{
public:
  /// Default constructor.
  ///
  /// Creates an empty point cloud.
  PointCloud();

  /// Constructor
  ///
  /// \param[in] positions Point positions
  /// \param[in] colors Point colors (r,g,b)
  /// \param[in] normals Point normals
  PointCloud(const std::vector<Vector3>& positions,
             const std::vector<Vector3>& colors = std::vector<Vector3>(),
             const std::vector<Vector3>& normals = std::vector<Vector3>());

  /// Constructor
  ///
  /// \param[in] count Number of points to reserve memory
  /// \param[in] hasColors Has colors (will reserve memory for colors)
  /// \param[in] hasNormals Has normals (will reserve memory for normals)
  PointCloud(const size_t count,
             const bool hasColors = false,
             const bool hasNormals = false);

  /// Constructor
  ///
  /// \param[in] positions Point positions
  /// \param[in] colors Point colors (r,g,b)
  /// \param[in] normals Point normals
  // PointCloud(std::vector<Vector3>&& positions);

  /// Get point count.
  ///
  /// \return Point count
  size_t pointCount() const;

  /// Add a point.
  ///
  /// This will expand the boundaries if needed.
  void addPoint(const Vector3& position);

  /// Add a point with color.
  ///
  /// This will expand the boundaries if needed.
  ///
  /// \param[in] position Point position
  /// \param[in] color Point color (r,g,b)
  void addPoint(const Vector3& position, const Vector3& color);

  /// Add a point with color and normal.
  ///
  /// This will expand the boundaries if needed.
  ///
  /// \param[in] position Point position
  /// \param[in] color Point color (r,g,b)
  /// \param[in] normal Point normal
  void addPoint(const Vector3& position,
                const Vector3& color,
                const Vector3& normal);

  // Positions

  /// Get a point position (by const reference).
  ///
  /// \param[in] index Point index
  /// \return Point position (x,y,z)
  const Vector3& position(size_t index) const;

  /// Get all point positions (by const reference)
  ///
  /// \return All point positions
  const std::vector<Vector3>& positions() const;

  // Colors

  /// Has color?
  ///
  /// True if colors are present, false otherwise
  bool hasColors() const;

  /// Get a point color (by reference).
  ///
  /// \param[in] index Point index
  /// \return Point color (r,g,b)
  Vector3& color(size_t index);

  /// Get a point color (by const reference).
  ///
  /// \param[in] index Point index
  /// \return Point color (r,g,b)
  const Vector3& color(size_t index) const;

  /// Get all point colors (by const reference)
  ///
  /// \return All point colors
  const std::vector<Vector3>& colors() const;

  // Normals

  /// Has normals?
  ///
  /// True if normals are present, false otherwise
  bool hasNormals() const;

  /// Get a point normal (by reference).
  ///
  /// \param[in] index Point index
  /// \return Point normal
  Vector3& normal(size_t index);

  /// Get a point normal (by const reference).
  ///
  /// \param[in] index Point index
  /// \return Point normal
  const Vector3& normal(size_t index) const;

  /// Get all point normals (by const reference)
  ///
  /// \return All point normals
  const std::vector<Vector3>& normals() const;

  // Shift

  /// Get origin shift (if any)
  ///
  /// \return Shift
  Vector3 shift() const;

  /// Set origin shift
  ///
  /// \param[in] shift Origin shift
  void setShift(const Vector3 &shift);

protected:
  std::vector<Vector3> m_positions;
  std::vector<Vector3> m_colors;
  std::vector<Vector3> m_normals;
  Vector3 m_shift;
};

/*
  // TODO: Create class Scalars

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

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_POINTCLOUD_H
