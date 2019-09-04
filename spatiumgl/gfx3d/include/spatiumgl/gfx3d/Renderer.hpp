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

#include "spatiumglexport.hpp"
#include "RenderObject.hpp"
#include "Camera.hpp"

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

			bool isValid() const
			{
				return m_valid;
			}

			virtual void render(Camera* camera, float aspect) = 0;

		protected:
			const RenderObject* m_renderObject;
			bool m_valid;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_RENDERER_H