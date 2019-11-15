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

namespace spatiumgl {
namespace gfx3d {

class SPATIUMGL_EXPORT PerspectiveCamera : public Camera
{
public:
  /// Constructor
  ///
  /// \param[in] fov Field of view angle
  /// \param[in] near Distance to near clipping plane
  /// \param[in] far Distance to far clipping plane
  PerspectiveCamera(double fov = 45, double near = 1, double far = 10);

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

protected:
  double m_fov;
};

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_PERSPECTIVECAMERA_H