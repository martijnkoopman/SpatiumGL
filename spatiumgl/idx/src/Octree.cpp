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

#include "spatiumgl/idx/Octree.hpp"

namespace spgl {
namespace idx {

BoundingCube
Octree::computeChildBounds(const BoundingCube& extent,
                           size_t childIndex)
{
  const double radius = extent.radius() / 2;

  switch (childIndex) {
    case 0:
      // Bottom front left
      return { extent.center() + Vector3(-radius, -radius, -radius), radius };
    case 1:
      // Bottom front right
      return { extent.center() + Vector3(radius, -radius, -radius), radius };
    case 2:
      // Bottom back left
      return { extent.center() + Vector3(-radius, radius, -radius), radius };
    case 3:
      // Bottom back right
      return { extent.center() + Vector3(radius, radius, -radius), radius };
    case 4:
      // Top front left
      return { extent.center() + Vector3(-radius, -radius, radius), radius };
    case 5:
      // Top front right
      return { extent.center() + Vector3(radius, -radius, radius), radius };
    case 6:
      // Top back left
      return { extent.center() + Vector3(-radius, radius, radius), radius };
    case 7:
      // Top back right
      return { extent.center() + Vector3(radius, radius, radius), radius };
    default:
      return extent;
  }
}

}
}
