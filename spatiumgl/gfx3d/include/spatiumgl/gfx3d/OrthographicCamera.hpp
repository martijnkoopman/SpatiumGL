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

#ifndef SPATIUMGL_GFX3D_ORTHOGRAPHICCAMERA_H
#define SPATIUMGL_GFX3D_ORTHOGRAPHICCAMERA_H

#include "Camera.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OrthographicCamera : public Camera
{
public:
  /// Constructor
  ///
  /// \param[in] size Orthographic size (y axis)
  /// \param[in] near Distance to near clipping plane (positive,
  ///                 absolute value)
  /// \param[in] far Distance to far clipping plane (positive,
  ///                absolute value)
  OrthographicCamera(double size, double near, double far);

  /// Destructor
  ~OrthographicCamera() override = default;

  /// Set orthographic size.
  ///
  /// \param[in] size Orthographic size
  void setSize(double size);

  /// Get orthographic size.
  ///
  /// \return Orthographic size
  double size() const;

  /// Get orthographic projection matrix.
  ///
  /// \param[in] aspect Aspect ratio (w/h)
  /// \return Orthographic projection matrix
  Matrix4 projectionMatrix(double aspect) const override;

protected:
  double m_size;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_ORTHOGRAPHICCAMERA_H