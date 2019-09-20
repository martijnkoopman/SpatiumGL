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

#ifndef SPATIUMGL_GFX3D_GLFWRENDERWINDOW_H
#define SPATIUMGL_GFX3D_GLFWRENDERWINDOW_H

#include "spatiumglexport.hpp"
#include "spatiumgl/gfx3d/RenderWindow.hpp"

#include <memory> // std::unique_ptr

namespace spatiumgl {
	namespace gfx3d {
		// Forward declaration of private implementation
		class GlfwRenderWindowImpl;

		/// \class GlfwRenderWindow
		/// \brief GLFW render window
		///
		/// This implementation is not tested for multiple windows.
		class SPATIUMGL_EXPORT GlfwRenderWindow : public RenderWindow
		{
			friend class GlfwRenderWindowImpl;

		public:
			/// Constructor
			GlfwRenderWindow(bool debug = false);

			/// Destructor
			virtual ~GlfwRenderWindow();

			/// Initialize GLFW.
			///
			/// Must be called before using most other GLFW functions.
			///
			/// \return True on success, false on failure.
			/// \sa terminate()
			bool init() override;

			/// Terminate GLFW.
			///
			/// \sa init()
			void terminate() const override;

			/// Create window and OpenGL context.
			///
			/// \param[in] width Window width
			/// \param[in] height Window height
			/// \return True on success, false when window or OpenGL context
			///	        creation fails.
			/// \sa destroyWindow()
			bool createWindow(int width, int height) override;

			/// Destroy window and OpenGL context.
			///
			/// \sa createWindow()
			void destroyWindow() override;

			/// Show the window.
			///
			/// This involves rendering the view and processing any user input.
			void show() override;

		private:
			std::unique_ptr<GlfwRenderWindowImpl> m_pimpl;
		};
	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_GLFWRENDERWINDOW_H