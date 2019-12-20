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

#ifndef SPATIUMGL_GFX3D_OCTREEOBJECT_H
#define SPATIUMGL_GFX3D_OCTREEOBJECT_H

#include "RenderObject.hpp"
#include "spatiumgl/idx/Octree.hpp"

namespace spgl {
namespace gfx3d {

/// \class OctreeObject
/// \brief Octree render object
class SPATIUMGL_EXPORT OctreeObject : public RenderObject
{
public:
  /// Constructor.
  ///
  /// PointCloudObject becomes owner of the point cloud.
  ///
  /// \param[in] pointCloud Point cloud
  OctreeObject(idx::Octree&& octree)
    : m_octree(std::move(octree))
  {
    m_bounds = BoundingBox<double>(m_octree.bounds().center(),
                                   { m_octree.bounds().radius(),
                                     m_octree.bounds().radius(),
                                     m_octree.bounds().radius() });
  }

  /// Get octree.
  ///
  /// \return Octree
  const idx::Octree& octree() const { return m_octree; }

  /// Get octree.
  ///
  /// \return Octree
  idx::Octree& octree() { return m_octree; }

protected:
  idx::Octree m_octree;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_OCTREEOBJECT_H
