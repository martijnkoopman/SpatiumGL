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

#ifndef SPATIUMGL_GFX3D_RENDERWINDOW_H
#define SPATIUMGL_GFX3D_RENDERWINDOW_H

#include "spatiumglexport.hpp"
#include "spatiumgl/Vector.hpp"
#include "spatiumgl/gfx3d/PivotInteractor.hpp"
#include "spatiumgl/gfx3d/RenderWindowInteractor.hpp"
#include "spatiumgl/gfx3d/Camera.hpp"
#include "spatiumgl/gfx3d/Renderer.hpp"

namespace spatiumgl {
	namespace gfx3d {

		class SPATIUMGL_EXPORT RenderWindow
		{
		public:
			/// Constructor
			RenderWindow(bool debug = false);

			/// Destructor
			virtual ~RenderWindow();

			// Abstract functions. To implement by inherited class
			virtual bool init() = 0;
			virtual bool createWindow(int width, int height) = 0;
			virtual void destroyWindow() = 0;
			virtual void terminate() const = 0;
			virtual void show() = 0;

			void setInteractor(RenderWindowInteractor* interactor);
			RenderWindowInteractor* interactor() const;
			void setCamera(Camera* camera);
			Camera* camera() const;
			void setRenderer(Renderer* renderer); // TODO: addRenderer
			Vector2i framebufferSize() const;

		protected:
			RenderWindowInteractor* m_interactor;
			Camera* m_camera;
      Renderer* m_renderer;
			Vector2i m_framebufferSize;
			bool m_debug;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_RENDERWINDOW_H
