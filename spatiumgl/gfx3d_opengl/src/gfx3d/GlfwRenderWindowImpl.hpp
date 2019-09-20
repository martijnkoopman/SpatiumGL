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

#ifndef SPATIUMGL_GFX3D_GLFWRENDERWINDOWIMPL_H
#define SPATIUMGL_GFX3D_GLFWRENDERWINDOWIMPL_H

#include "spatiumgl/gfx3d/GlfwRenderWindow.hpp"

#include <GL/glew.h> // Include GLEW *always* just before GLFW.
#include <GLFW/glfw3.h> // GLFWwindow

namespace spatiumgl {
	namespace gfx3d {

		class GlfwRenderWindowImpl
		{
		public:
			/// Constructor
			/// \param[in] parent Parent implementation
			/// \param[in] debug Log debug information
			GlfwRenderWindowImpl(GlfwRenderWindow* parent, bool debug = false);

			// Destructor
			~GlfwRenderWindowImpl() = default;

			bool init();
			bool createWindow(int width, int height);
			void destroyWindow();
			void terminate() const;
			void show();

		protected:
			void draw();
			void processUserInput();

			// GLFW callback functions
			void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
			void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			void glfw_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
			void glfw_scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
			static void glfw_error_callback(int error, const char* description);

			GlfwRenderWindow* m_parent;
			GLFWwindow* m_window;
			int prevMouseState = GLFW_RELEASE;
			double prevMouseX, prevMouseY;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_GLFWRENDERWINDOWIMPL_H