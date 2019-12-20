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

#ifndef SPATIUMGL_GFX3D_PERSPECTIVECAMERA_H
#define SPATIUMGL_GFX3D_PERSPECTIVECAMERA_H

#include "Camera.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT PerspectiveCamera : public Camera
{
public:
  /// Constructor
  ///
  /// \param[in] fov Field of view angle
  /// \param[in] near Distance to near clipping plane
  /// \param[in] far Distance to far clipping plane
  PerspectiveCamera(double fov = 0.7853981634,
                    double near = 1,
                    double far = 10);

  /// Destructor
  virtual ~PerspectiveCamera() override = default;

  /// Set field of view angle (vertical) (radians).
  ///
  /// \param[in] field of view angle
  void setFov(double fov);

  /// Get vield of view angle (vertical) (radians).
  ///
  /// \return Field of view angle
  double fov() const;

  /// Get perspective projection matrix.
  ///
  /// \param[in] aspect Aspect ratio (w/h)
  /// \return Perspective projection matrix
  Matrix4 projectionMatrix(double aspect) const override;

  /// Transform point from world space into viewport space.
  ///
  /// Viewport space is normalized and relative to the camera. The bottom-left 
  /// of the camera is (0,0)(-1,-1)?; the top-right is (1,1). The z position 
  /// is in world units from the camera.
  ///
  /// \param[in] point World point
  /// \param[in] aspect Aspect ratio (w/h)
  /// \return Viewport point
  Vector3 worldToViewportPoint(const Vector3& point, double aspect) const;

  /// Transform point from world space into screen space.
  ///
  /// Screenspace is defined in pixels. The bottom-left of the screen is (0,0);
  /// the right-top is (pixelWidth,pixelHeight). The z position is in world 
  /// units from the camera.
  ///
  /// \param[in] point World point
  /// \param[in] size Screen size in pixels
  /// \return Screen point
  Vector3 worldToScreenPoint(const Vector3& point, const Vector2i &size) const;

  //Vector3 screenToWorldPoint(const Vector3& point) const;

  //Vector3 screenToWorldPoint(const Vector3& point) const;

protected:
  double m_fov;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_PERSPECTIVECAMERA_H
