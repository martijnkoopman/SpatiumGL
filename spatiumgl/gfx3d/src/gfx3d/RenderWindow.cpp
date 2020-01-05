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

#include "spatiumgl/gfx3d/RenderWindow.hpp"
#include "spatiumgl/gfx3d/PivotInteractor.hpp"

namespace spgl {
namespace gfx3d {
RenderWindow::RenderWindow(bool debug)
  : m_interactor(nullptr)
  , m_camera(nullptr)
  , m_renderers()
  , m_animators()
  , m_framebufferSize{ 0, 0 }
  , m_debug(debug)
{}

void
RenderWindow::setInteractor(RenderWindowInteractor* interactor)
{
  m_interactor = interactor;
}

RenderWindowInteractor*
RenderWindow::interactor() const
{
  return m_interactor;
}

void
RenderWindow::setCamera(Camera* camera)
{
  m_camera = camera;
}

Camera*
RenderWindow::camera() const
{
  return m_camera;
}

void
RenderWindow::addRenderer(Renderer* renderer)
{
  m_renderers.push_back(renderer);

  if (m_renderers.size() == 1) {
    m_bounds = renderer->renderObject().bounds();
  } else {
    m_bounds.include(renderer->renderObject().bounds());
  }
}

BoundingBox
RenderWindow::bounds() const
{
  return m_bounds;
}

void
RenderWindow::addAnimator(Animator* animator)
{
  m_animators.push_back(animator);
}

Vector2i
RenderWindow::framebufferSize() const
{
  return m_framebufferSize;
}
} // namespace gfx3d
} // namespace spgl
