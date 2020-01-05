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

#include "spatiumgl/gfx3d/Scalars.hpp"
#include "spatiumgl/Bounds.hpp"
#include "spatiumgl/Vector.hpp"
#include "spatiumglexport.hpp"

#include <vector>

namespace spgl {
namespace gfx3d {

/// \class PointCloudData
///
/// A point cloud data contains the actual point cloud: points, colors and
/// scalars.
struct SPATIUMGL_EXPORT PointCloudData
{
public:
  /// Constructor.
  ///
  /// The PointCloudData becomes owner of the data (moved).
  ///
  /// \param[in] positions Point positions
  /// \param[in] colors Point colors (RGB) (optional)
  /// \param[in] scalars Point scalars (optional)
  PointCloudData(std::vector<Vector3f>&& positions,
                 std::vector<Vector3f>&& colors = std::vector<Vector3f>(),
                 Scalars<float>&& scalars = Scalars<float>())
    : m_positions(std::move(positions))
    , m_colors(std::move(colors))
    , m_scalars(std::move(scalars))
  {}

  /// Clear all data.
  ///
  /// Clears points, colors and scalars.
  void clear()
  {
    std::vector<Vector3f>().swap(m_positions);
    std::vector<Vector3f>().swap(m_colors);
    m_scalars.clear();
  }

  /// Get point positions (by const reference)
  ///
  /// \return Point positions
  const std::vector<Vector3f>& positions() const { return m_positions; }

  /// Get point colors (by const reference)
  ///
  /// \return Point colors
  const std::vector<Vector3f>& colors() const { return m_colors; }

  /// Get point scalars (by const reference)
  ///
  /// \return Point scalars
  const Scalars<float>& scalars() const { return m_scalars; }

  /// Compute size in bytes.
  ///
  /// \return Size
  size_t computeSize() const
  {
    return m_positions.capacity() * sizeof(Vector3f) +
           m_scalars.values().capacity() * sizeof(float) +
           m_colors.capacity() * sizeof(Vector3f);
  }

protected:
  std::vector<Vector3f> m_positions;
  std::vector<Vector3f> m_colors;
  Scalars<float> m_scalars;
};

/// \class PointCloudHeader
///
/// A point cloud header contains metadata about a point cloud.
struct SPATIUMGL_EXPORT PointCloudHeader
{
public:
  /// Constructor
  ///
  /// \param[in] pointCount Point count
  /// \param[in] hasColors Points have colors
  /// \param[in] hasScalars Points have scalars
  /// \param[in] shift Origin shift applied on points
  /// \param[in] extent Spatial extent of all points (without shift)
  PointCloudHeader(size_t pointCount,
                   bool hasColors,
                   bool hasScalars,
                   const BoundingBox extent)
    : m_pointCount(pointCount)
    , m_hasColors(hasColors)
    , m_hasScalars(hasScalars)
    , m_extent(extent)
  {}

  /// Construct from point cloud data.
  ///
  /// Beware: This functions iterates ALL points to compute the header values
  /// and therefore can be suboptimal for large point clouds. It is recommended
  /// to determine the header values in advance and construct the header using
  /// the provided constructor instead of this function.
  ///
  /// \param[in] data Point cloud data
  /// \return Point cloud header
  static PointCloudHeader constructFromData(const PointCloudData& data)
  {
    const size_t count = data.positions().size();
    const bool hasColors = data.colors().size() == count && count > 0;
    const bool hasScalars = data.scalars().values().size() == count && count > 0;

    // Compute extent
    auto computeExtent =
      [&](const std::vector<Vector3f>& positions) -> BoundingBox {
      if (positions.size() < 1) {
        return {};
      } else {
        // Set initial extent
        BoundingBox extent(positions[0].staticCast<double>(), {});

        // Iterate points and update extent
        for (size_t i = 1; i < positions.size(); i++) {
          extent.include(positions[i].staticCast<double>());
        }
        return extent;
      }
    };

    return {
      count, hasColors, hasScalars, computeExtent(data.positions())
    };
  }

  // Compare operators

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other point cloud header
  /// \return True if equal, otherwise false
  bool operator==(const PointCloudHeader& other) const
  {
    if (this->m_pointCount != other.m_pointCount ||
        this->m_hasColors != other.m_hasColors ||
        this->m_hasScalars != other.m_hasScalars ||
        this->m_extent != other.m_extent) {
      return false;
    }
    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other point cloud header
  /// \return True if unequal, otherwise false
  bool operator!=(const PointCloudHeader& other) const
  {
    return !(operator==(other));
  }

  // Getters

  /// Get point count.
  ///
  /// \return Point count
  size_t pointCount() const { return m_pointCount; }

  /// Has colors?
  ///
  /// True if colors are present, false otherwise
  bool hasColors() const { return m_hasColors; }

  /// Has scalars?
  ///
  /// True if scalars are present, false otherwise
  bool hasScalars() const { return m_hasScalars; }

  /// Get spatial extent.
  ///
  /// \return Extent
  BoundingBox extent() const { return m_extent; }

protected:
  size_t m_pointCount;
  bool m_hasColors;
  bool m_hasScalars;
  BoundingBox m_extent;
};

/// \class PointCloud
/// \brief Point cloud
///
/// A point cloud is a collection of points with optionally colors and scalars.
/// A point cloud is immutable; no points, colors or scalars can be added or
/// removed. The datastructure consists of a header and data. The header
/// contains metadata like point count, extent, etc. The data contains the
/// actual points, colors and scalars. The data can be cleared while the header
/// remains. This is for example useful after a point cloud has been mapped to
/// GPU memory.
class SPATIUMGL_EXPORT PointCloud
{
public:
  /// Constructor.
  ///
  /// The PointCloud becomes owner of the data (is moved). The header is
  /// simply copied.
  ///
  /// \param[in] header Point cloud header
  /// \param[in] data Point cloud data
  PointCloud(const PointCloudHeader& header, PointCloudData&& data)
    : m_header(header)
    , m_data(std::move(data))
  {}

  /// Get point cloud header (by const reference).
  ///
  /// \return Header
  /// \sa PointCloudHeader
  const PointCloudHeader& header() const { return m_header; }

  /// Get point cloud data (by reference).
  ///
  /// \return Data
  /// \sa PointCloudData
  PointCloudData& data() { return m_data; }

  /// Get point cloud data (by const reference).
  ///
  /// \return Data
  /// \sa PointCloudData
  const PointCloudData& data() const { return m_data; }

protected:
  PointCloudHeader m_header;
  PointCloudData m_data;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_POINTCLOUD_H
