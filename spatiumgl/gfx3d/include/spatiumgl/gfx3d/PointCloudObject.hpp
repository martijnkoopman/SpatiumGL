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

#ifndef SPATIUMGL_GFX3D_POINTCLOUDOBJECT_H
#define SPATIUMGL_GFX3D_POINTCLOUDOBJECT_H

#include "RenderObject.hpp"
#include "PointCloud.hpp"

namespace spatiumgl {
namespace gfx3d {

/// \class PointCloudObject
/// \brief Point cloud render object
class SPATIUMGL_EXPORT PointCloudObject : public RenderObject
{
public:
  /// Constructor.
  ///
  /// PointCloudObject becomes owner of the point cloud.
  ///
  /// \param[in] pointCloud Point cloud
  PointCloudObject(PointCloud&& pointCloud)
    : m_pointCloud(std::move(pointCloud))
  {
    m_bounds = m_pointCloud.header().extent();
  }

  /// Get point cloud (by const reference)
  ///
  /// \return Point cloud
  const PointCloud& pointCloud() const { return m_pointCloud; }

protected:
  PointCloud m_pointCloud;
};

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_POINTCLOUDOBJECT_H
