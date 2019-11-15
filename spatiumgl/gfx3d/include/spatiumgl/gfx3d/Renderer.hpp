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

#ifndef SPATIUMGL_GFX3D_RENDERER_H
#define SPATIUMGL_GFX3D_RENDERER_H

#include "Camera.hpp"
#include "RenderObject.hpp"
#include "spatiumglexport.hpp"

namespace spatiumgl {
namespace gfx3d {

class SPATIUMGL_EXPORT Renderer
{
public:
  Renderer(const RenderObject* renderObject)
    : m_renderObject(renderObject)
    , m_valid(false)
  {}

  virtual ~Renderer() = default;

  /// Get boolean indicator if renderer is valid.
  ///
  /// A renderer may be invalid, for example, if its capabilites aren't
  /// supported by the GPU hardware.
  ///
  /// \return True if valid, false otherwise.
  bool isValid() const { return m_valid; }

  /// Get the render object (by const reference)
  ///
  /// \return Render object
  const RenderObject& renderObject() const { return *m_renderObject; }

  /// Render the render object.
  ///
  /// This function should be called by the RenderWindow.
  ///
  /// \param[in] camera Camera
  /// \param[in] aspect Aspect ratio (w/h)
  virtual void render(Camera* camera, double aspect) = 0;

protected:
  const RenderObject* m_renderObject;
  bool m_valid;
};

} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_RENDERER_H