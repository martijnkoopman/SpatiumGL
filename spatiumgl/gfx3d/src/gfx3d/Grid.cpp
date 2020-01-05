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

#include "spatiumgl/gfx3d/Grid.hpp"

namespace spgl {
namespace gfx3d {

Grid::Grid(const size_t radiusX,
           const size_t radiusY,
           const double spacingX,
           const double spacingY)
  : RenderObject()
  , m_radiusX(radiusX)
  , m_radiusY(radiusY)
  , m_spacingX(spacingX)
  , m_spacingY(spacingY)
{
  m_bounds = BoundingBox(
    { 0, 0, 0 }, { m_radiusX * m_spacingX, m_radiusY * m_spacingY, 0 });
}

} // namespace gfx3d
} // namespace spgl
