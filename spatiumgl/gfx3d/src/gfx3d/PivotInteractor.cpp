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

#include "spatiumgl/gfx3d/PivotInteractor.hpp"
#include "spatiumgl/Math.hpp"
#include "spatiumgl/gfx3d/OrthographicCamera.hpp"
#include "spatiumgl/gfx3d/PerspectiveCamera.hpp"
#include "spatiumgl/gfx3d/RenderWindow.hpp"

#include <algorithm> // std::max

namespace spgl {
namespace gfx3d {

PivotInteractor::PivotInteractor(RenderWindow* window)
  : RenderWindowInteractor(window)
  , m_pressedLeft(false)
  , m_pressedRight(false)
  , m_pivotPoint()
{}

void
PivotInteractor::setPivotPoint(const Vector3& pivotPoint)
{
  m_pivotPoint = pivotPoint;
}

Vector3
PivotInteractor::pivotPoint() const
{
  return m_pivotPoint;
}

void
PivotInteractor::OnMouseButtonPressed(MouseButton button, double x, double y)
{
  switch (button) {
    case MouseButton::MOUSE_BUTTON_LEFT:
      m_pressedLeft = true;
      break;
    case MouseButton::MOUSE_BUTTON_RIGHT:
      m_pressedRight = true;
      break;
  }
}

void
PivotInteractor::OnMouseButtonReleased(MouseButton button, double x, double y)
{
  switch (button) {
    case MouseButton::MOUSE_BUTTON_LEFT:
      m_pressedLeft = false;
      break;
    case MouseButton::MOUSE_BUTTON_RIGHT:
      m_pressedRight = false;
      break;
  }
}

void
PivotInteractor::OnMouseWheelScrolled(double scroll)
{
  Camera* camera = m_window->camera();
  if (camera != nullptr) {
    Vector3 directionOfProjection =
      (camera->transform().translation() - m_pivotPoint);

    if (scroll < 0) {
      // Zoom out
      Vector3 translation = directionOfProjection * -scroll;
      camera->transform().translate(translation);
    } else if (scroll > 0) {
      // Zoom in
      Vector3 translation = directionOfProjection / (-scroll * 2);
      camera->transform().translate(translation);
    }

    // Update camera clipping distances based on scene content.
    camera->setNearAndFarFromBounds(m_window->bounds());

    // Update orthographic camera size
    auto orthoCamera = dynamic_cast<OrthographicCamera*>(camera);
    if (orthoCamera != nullptr) {
      orthoCamera->setSize(directionOfProjection.length());
    }
  }
}

void
PivotInteractor::OnMouseMoved(double deltaX, double deltaY)
{
  if (m_pressedLeft || m_pressedRight) {
    const Vector2i framebufferSize = m_window->framebufferSize();
    Camera* camera = m_window->camera();

    if (framebufferSize[0] > 0 && framebufferSize[1] > 0 && camera != nullptr) {

      // Rotate view
      if (m_pressedLeft) {
        // Get rotation angles
        const double angleX = deltaX * PI<double>() / framebufferSize[0];
        const double angleY = deltaY * PI<double>() / framebufferSize[1];

        // Translate pivot point to origin
        camera->transform().translate(m_pivotPoint * -1);

        // Rotate around horizontal and vertical axes
        camera->transform().rotateAround(camera->transform().up(), -angleX);
        camera->transform().rotateAround(camera->transform().right(), -angleY);

        // Translate back to pivot point
        camera->transform().translate(m_pivotPoint);

        // camera->orthogonalizeViewUp();
      }

      // Pan view
      if (m_pressedRight) {
        auto perspectiveCamera =
          dynamic_cast<PerspectiveCamera*>(m_window->camera());
        if (perspectiveCamera != nullptr) {
          // Perspective camera

          // Compute translation vector
          const double distance =
            (camera->transform().translation() - m_pivotPoint).length();

          const double angleY =
            perspectiveCamera->fov() * deltaY / framebufferSize[1];
          const double translateY = tan(angleY) * distance;

          const double aspectRatio = framebufferSize[0] / framebufferSize[1];
          const double angleX = perspectiveCamera->fov() * aspectRatio *
                                deltaX / framebufferSize[0];
          const double translateX = tan(angleX) * distance;
          Vector3 translation = (camera->transform().up() * translateY) -
                                (camera->transform().right() * translateX);

          // Apply translation to camera and pivot point
          camera->transform().translate(translation);
          m_pivotPoint = m_pivotPoint + translation;

        } else {
          // Orthographic camera

          /// \todo implement pan for orthographic camera (using orthographic
          /// size)
        }
      }
    }
  }
}

void
PivotInteractor::resetCamera()
{
  // Set pivot point to center of bounds
  m_pivotPoint = m_window->bounds().center();

  auto perspectiveCamera = dynamic_cast<PerspectiveCamera*>(m_window->camera());
  if (perspectiveCamera != nullptr) {

    // Fit in view vertically
    const double z1 =
      m_window->bounds().radii()[1] / tan(perspectiveCamera->fov() / 2);

    // Fit in view horizontally
    const double fovX = perspectiveCamera->fov() *
                        m_window->framebufferSize()[0] /
                        m_window->framebufferSize()[1];
    const double z2 = m_window->bounds().radii()[0] / tan(fovX / 2);

    // Choose maximum distance and add 10%
    double z = std::max(z1, z2);
    z = z * 1.1 + m_window->bounds().max()[2];

    // Position camera above, looking down with Y+ up vector.
    m_window->camera()->lookAt(
      m_pivotPoint, Vector3(0, 1, 0), m_pivotPoint + Vector3(0, 0, z));
  }
  /// \todo Implement for orthographic camera

  resetCameraClipping();
}

void
PivotInteractor::resetCameraClipping()
{
  m_window->camera()->setNearAndFarFromBounds(m_window->bounds());
}

} // namespace gfx3d
} // namespace spgl
