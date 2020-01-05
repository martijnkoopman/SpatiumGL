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

#ifndef SPATIUMGL_GFX3D_PLANEINTERACTOR_H
#define SPATIUMGL_GFX3D_PLANEINTERACTOR_H

#include "spatiumglexport.hpp"
#include "RenderWindowInteractor.hpp"
#include "spatiumgl/Vector.hpp"

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT PlaneInteractor : public RenderWindowInteractor
{
public:
  /// Constructor
  ///
  /// \param[in] window Render window
  PlaneInteractor(RenderWindow* window);

  /// Destructor
  virtual ~PlaneInteractor() override = default;

  /// Set the pivot point.
  ///
  /// This is the point around which the view rotates.
  ///
  /// \param[in] pivotPoint Pivot point
  void setPivotPoint(const Vector3& pivotPoint);

  /// Get pivot point.
  ///
  /// \return Pivot point
  Vector3 pivotPoint() const;

  void OnMouseButtonPressed(MouseButton button, double x, double y) override;
  void OnMouseButtonReleased(MouseButton button, double x, double y) override;
  void OnMouseWheelScrolled(double scroll) override;
  void OnMouseMoved(double deltaX, double deltaY) override;

  /// Reset camera transform and clipping distances.
  ///
  /// Reposition the camera and ensure the scene isn't clipped.
  /// This places the camera above the scene (along the Z-axis) while
  /// looking down and the positive Y-axis pointing up.
  void resetCamera() override;

  void resetCameraClipping() override;

protected:
  bool m_pressedLeft;
  bool m_pressedRight;
  Vector3 m_pivotPoint;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_PLANEINTERACTOR_H
