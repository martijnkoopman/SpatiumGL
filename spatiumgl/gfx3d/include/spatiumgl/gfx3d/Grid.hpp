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

#ifndef SPATIUMGL_GFX3D_GRID_H
#define SPATIUMGL_GFX3D_GRID_H

#include "RenderObject.hpp"
#include "spatiumglexport.hpp"

#include <ostream>
#include <vector>

namespace spgl {
namespace gfx3d {

/// \class Grid
/// \brief Quadrangular grid lines
///
/// ...
class SPATIUMGL_EXPORT Grid : public RenderObject
{
public:
  /// Constructor
  ///
  /// \param[in] radiusX Radius on X axis
  /// \param[in] radiusY Radius on Y axis
  /// \param[in] spacingX Spacing on X axis
  /// \param[in] spacingY Spacing on Y axis
  Grid(size_t radiusX, size_t radiusY, double spacingX, double spacingY);

  /// Destructor
  virtual ~Grid() = default;

  size_t radiusX() const { return m_radiusX; }
  size_t radiusY() const { return m_radiusY; }
  double spacingX() const { return m_spacingX; }
  double spacingY() const { return m_spacingY; }

protected:
  size_t m_radiusX;
  size_t m_radiusY;
  double m_spacingX;
  double m_spacingY;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_GRID_H
