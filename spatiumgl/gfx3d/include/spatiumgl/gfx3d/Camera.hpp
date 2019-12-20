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

#ifndef SPATIUMGL_GFX3D_CAMERA_H
#define SPATIUMGL_GFX3D_CAMERA_H

#include "SceneObject.hpp"
#include "spatiumgl/Bounds.hpp"
#include "spatiumglexport.hpp"

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT Camera : public SceneObject
{
public:
  /// Constructor
  ///
  /// \param[in] near Distance to near clipping plane
  /// \param[in] far Distance to far clipping plane
  Camera(double near, double far);

  /// Destructor
  virtual ~Camera() = default;

  /// Get the distance to the near clipping plane in world space.
  ///
  /// \return Near clipping plane distance.
  double near() const;

  /// Get the distance to the far clipping plane in world space.
  ///
  /// \return Far clipping plane distance.
  double far() const;

  /// Set view direction towards target position.
  /// The resulting transformation matrix maps the reference point to the
  /// negative z axis and the eye point to the origin.
  ///
  /// \param[in] target Target position
  /// \param[in] up Up vector
  ///                May not be parallel with view direction vector
  void lookAt(const Vector3& target, const Vector3& up);

  /// Set camera position and set view direction towards target position.
  /// The resulting transformation matrix maps the reference point to the
  /// negative z axis and the eye point to the origin.
  ///
  /// \param[in] target Target position
  /// \param[in] up Up vector
  ///                May not be parallel with vector from eye to target
  /// \param[in] eye Camera/eye position
  void lookAt(const Vector3& target, const Vector3& up, const Vector3& eye);

  void orthogonalizeViewUp();

  /// Set the near and far clipping plane distances to include certain
  /// boundaries.
  ///
  /// \param[in] bounds Boundaries
  void setNearAndFarFromBounds(const BoundingBox<double>& bounds);

  /// Get the projection matrix.
  ///
  /// \param[in] aspect Aspect ratio (w/h)
  /// \return Projection matrix
  virtual Matrix4 projectionMatrix(double aspect) const = 0;

  //virtual Vector3 worldToViewportPoint(const Vector3& point,
  //                                    double aspect) const = 0;
  //virtual Vector3 worldToScreenPoint(const Vector3& point,
  //                                   const Vector2i& size) const = 0;

protected:
  double m_near;
  double m_far;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_CAMERA_H
