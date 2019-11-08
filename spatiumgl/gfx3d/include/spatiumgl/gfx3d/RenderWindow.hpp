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
#include "spatiumgl/gfx3d/RenderWindowInteractor.hpp"
#include "spatiumgl/gfx3d/Camera.hpp"
#include "spatiumgl/gfx3d/Renderer.hpp"
#include "spatiumgl/gfx3d/Animator.hpp"
#include "spatiumgl/Vector.hpp"

#include <vector> // std::vector

namespace spatiumgl {
	namespace gfx3d {
		class SPATIUMGL_EXPORT RenderWindow
		{
		public:
			/// Constructor
			///
			/// \param[in] debug Log debug information
			RenderWindow(bool debug = false);

			/// Destructor
			virtual ~RenderWindow();

			/// Set the render window interactor.
			///
			/// \param[in] interactor Render window interactor
			void setInteractor(RenderWindowInteractor* interactor);

			/// Get the render window interactor.
			///
			/// \return Render window interactor
			RenderWindowInteractor* interactor() const;

			/// Set the camera.
			///
			/// \param[in] camera Camera
			void setCamera(Camera* camera);

			/// Get the camera
			///
			/// \return Camera
			Camera* camera() const;

			/// Add a renderer 
			///
			/// \param[in] renderer Renderer
			void addRenderer(Renderer* renderer);

			/// Get the boundaries of all renderers combined, i.e., the entire 
			/// scene.
			/// 
			/// \return Scene boundaries
			BoundingBox<SPATIUMGL_PRECISION> bounds() const;

			/// Add an animator
			///
			/// \param[in] animator Animator
			void addAnimator(Animator* animator);

			Vector2i framebufferSize() const;

			// Pure virtual functions to be implemented by subclasses.

			/// Initialize the library responsible for window and OpenGL 
			/// context creation.
			///
			/// \return True on success, false otherwise.
			/// \sa terminate()
			virtual bool init() = 0;

			/// Terminate the library responsible for window and OpenGL 
			/// context creation.
			///
			/// \sa init()
			virtual void terminate() const = 0;

			/// Create window and OpenGL context.
			///
			/// \param[in] width Window width
			/// \param[in] height Window height
			/// \return True on success, false when window or OpenGL context
			///	        creation fails.
			/// \sa destroyWindow()
			virtual bool createWindow(int width, int height) = 0;

			/// Destroy window and OpenGL context.
			///
			/// \sa createWindow()
			virtual void destroyWindow() = 0;

			/// Show the window.
			virtual void show() = 0;

		protected:
			RenderWindowInteractor* m_interactor;
			Camera* m_camera;
			std::vector<Renderer*> m_renderers;
			std::vector<Animator*> m_animators;

			BoundingBox<SPATIUMGL_PRECISION> m_bounds;

			Vector2i m_framebufferSize;
			bool m_debug;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_RENDERWINDOW_H