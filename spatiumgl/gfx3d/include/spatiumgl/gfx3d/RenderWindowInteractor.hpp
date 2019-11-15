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

#ifndef SPATIUMGL_GFX3D_RENDERWINDOWINTERACTOR_H
#define SPATIUMGL_GFX3D_RENDERWINDOWINTERACTOR_H

#include "spatiumglexport.hpp"

namespace spatiumgl {
namespace gfx3d {

// Forward declare
class RenderWindow;

class SPATIUMGL_EXPORT RenderWindowInteractor
{
public:
  enum MouseButton
  {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_RIGHT
  };

  /// Constructor
  ///
  /// \param[in] window Render window
  RenderWindowInteractor(RenderWindow* window)
    : m_window(window)
  {}

  /// Destructor
  virtual ~RenderWindowInteractor() = default;

  // Pure virtual functions to be implemented by subclasses.

  virtual void OnMouseButtonPressed(MouseButton button, double x, double y) = 0;
  virtual void OnMouseButtonReleased(MouseButton button,
                                     double x,
                                     double y) = 0;
  virtual void OnMouseWheelScrolled(double scroll) = 0;
  virtual void OnMouseMoved(double deltaX, double deltaY) = 0;

  // virtual void OnKeyPressed(int key) = 0;
  // virtual void OnKeyRepeated(int key) = 0;
  // virtual void OnKeyReleased(int key) = 0;

  /// Reset camera transform and clipping distances.
  ///
  /// Reposition the camera and ensure the scene isn't clipped.
  virtual void resetCamera() = 0;

  /// Reset camera clipping distances.
  ///
  /// Ensure the scene isn't clipped.
  virtual void resetCameraClipping() = 0;

protected:
  RenderWindow* m_window;
};

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_RENDERWINDOWINTERACTOR_H
