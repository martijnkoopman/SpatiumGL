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

#include "spatiumgl/gfx3d/GlfwRenderWindow.hpp" 

#include <GL/glew.h> // Include GLEW *always* just before GLFW.
#include <GLFW/glfw3.h> // GLFWwindow

#include <iostream>
#include <string>

namespace spatiumgl {
	namespace gfx3d {

		static void opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			std::string typeStr("unknown");
			switch (type)
			{
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				typeStr = "DEPRECATED_BEHAVIOR";
				break;
			case GL_DEBUG_TYPE_ERROR:
				typeStr = "ERROR";
				break;
			case GL_DEBUG_TYPE_MARKER:
				typeStr = "MARKER";
				break;
			case GL_DEBUG_TYPE_OTHER:
				typeStr = "OTHER";
				break;
			case GL_DEBUG_TYPE_PERFORMANCE:
				typeStr = "PERFORMANCE";
				break;
			case GL_DEBUG_TYPE_PORTABILITY:
				typeStr = "PORTABILITY";
				break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				typeStr = "UNDEFINED_BEHAVIOR";
				break;
			}

			std::string severityStr("unknown");
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_LOW:
				severityStr = "LOW";
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				severityStr = "MEDIUM";
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				severityStr = "HIGH";
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				severityStr = "NOTIFICATION";
				break;
			}

			std::string messageStr(message);
			std::cerr << "GL CALLBACK: type = " << typeStr <<
				", severity = " << severityStr <<
				", message = " << messageStr << std::endl;
		}

		class GlfwRenderWindow::impl
		{
		public:
			// Constructor
			impl(GlfwRenderWindow* parent, bool debug = false)
				: m_parent(parent)
				, m_window(nullptr)
				, prevMouseState(GLFW_RELEASE)
				, prevMouseX(0)
				, prevMouseY(0)
			{
			}

			// Destructor
			~impl()
			{

			}

			bool init()
			{
				// Set error calback function
				glfwSetErrorCallback(&impl::glfw_error_callback);

				// Initialize GLFW (After this always terminate)
				if (!glfwInit())
				{
					return false;
				}

				return true;
			}

			bool createWindow(int width, int height)
			{
				// Create window with OpenGL context
				m_window = glfwCreateWindow(width, height, "SpatiumGL Render Window", NULL, NULL);
				if (!m_window)
				{
					fprintf(stderr, "Failed to create window or OpenGL context.\n");

					// Release resources of GLFW
					glfwTerminate();
					return false;
				}
				glfwSetWindowUserPointer(m_window, this);

				// Make OpenGL context of window current
				glfwMakeContextCurrent(m_window);

				// Initialize GLEW extension loader library
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					fprintf(stderr, "Error: %s\n", glewGetErrorString(glewError));

					// Exit
					glfwTerminate();
					return false;
				}

				// Print OpenGL version in use
				std::cout << "OpenGL version: " << reinterpret_cast<char const*>(glGetString(GL_VERSION)) << std::endl;
				std::cout << "GLSL version: " << reinterpret_cast<char const*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;

				// Capture OpenGL debug output
				if (m_parent->m_debug)
				{
					glEnable(GL_DEBUG_OUTPUT);
					glDebugMessageCallback(opengl_error_callback, NULL);
				}

				// Capture frame buffer resize event (is not equal to window size)
				glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* win, int w, int h)
					{
						static_cast<impl*>(glfwGetWindowUserPointer(win))->glfw_framebuffer_size_callback(win, w, h);
					});

				// Get current frame buffer size
				glfwGetFramebufferSize(m_window, &m_parent->m_framebufferSize[0], &m_parent->m_framebufferSize[1]); // m_framebufferSize.data(), m_framebufferSize.data() + 1);

				// Set swap interval of front and back buffer to 1 frame instead of 0 (immediate)
				glfwSwapInterval(1);

				// Capture user input events

				// Input event: mouse button
				glfwSetMouseButtonCallback(m_window, [](GLFWwindow* win, int but, int act, int mod)
					{
						static_cast<impl*>(glfwGetWindowUserPointer(win))->glfw_mouse_button_callback(win, but, act, mod);
					});

				// Input event: cursor position
				glfwSetCursorPosCallback(m_window, [](GLFWwindow* win, double x, double y)
					{
						static_cast<impl*>(glfwGetWindowUserPointer(win))->glfw_cursor_pos_callback(win, x, y);
					});

				// Input event: scroll 
				glfwSetScrollCallback(m_window, [](GLFWwindow* win, double xOff, double yOff)
					{
						static_cast<impl*>(glfwGetWindowUserPointer(win))->glfw_scroll_callback(win, xOff, yOff);
					});

				return true;
			}

			void destroyWindow()
			{
				// Destroy window and OpenGL context
				glfwDestroyWindow(m_window);

				m_window = nullptr;
			}

			void terminate() const
			{
				glfwTerminate();
			}

			void show()
			{
				// Keep running as long as window shouldn't be closed
				while (!glfwWindowShouldClose(m_window))
				{
					// Draw frame
					draw();

					processUserInput();

					// Process events
					glfwPollEvents();
				}
			}

		protected:

			void draw()
			{
				// Clear color buffer (dark gray)
				glClearColor(0.227f, 0.227f, 0.227f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT); // Depth (Also glEnable(depth)

				m_parent->m_renderer->render(m_parent->m_camera, (float)m_parent->m_framebufferSize[0] / (float)m_parent->m_framebufferSize[1]);

				// Swap front and back buffer (front = displayed, back = rendered)
				glfwSwapBuffers(m_window);
			}

			void processUserInput()
			{
				// Check keyboard input
				if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				{
					glfwSetWindowShouldClose(m_window, true);
				}

				// Check mouse movement
				double mousePosX, mousePosY;
				glfwGetCursorPos(m_window, &mousePosX, &mousePosY);

				// Emit mouse left button state changed
				int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
				if (state == GLFW_PRESS && prevMouseState == GLFW_RELEASE)
				{
					m_parent->m_interactor->OnMousePressed(RenderWindowInteractor::MOUSE_BUTTON_LEFT, mousePosX, mousePosY);
				}
				else if (state == GLFW_RELEASE && prevMouseState == GLFW_PRESS)
				{
					m_parent->m_interactor->OnMouseReleased(RenderWindowInteractor::MOUSE_BUTTON_LEFT, mousePosX, mousePosY);
				}

				// Emit mouse moved
				double deltaX = mousePosX - prevMouseX;
				double deltaY = mousePosY - prevMouseY;
				if (deltaX > 0.00 || deltaX < -0.00 || deltaY > 0.00 || deltaY < -0.00)
				{
					m_parent->m_interactor->OnMouseMoved(deltaX, deltaY);
				}

				prevMouseState = state;
				prevMouseX = mousePosX;
				prevMouseY = mousePosY;
			}

			// GLFW callback functions:

			void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
			{
				// Store current viewport size
				m_parent->m_framebufferSize[0] = width;
				m_parent->m_framebufferSize[1] = height;

				// Set viewport size
				glViewport(0, 0, width, height);

				// Draw during window resize
				draw();
			}

			void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
			{
				std::cout << "Button " << button << " " << action << " " << mods << std::endl;
			}

			void glfw_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
			{
				std::cout << "Cursor " << xpos << " " << ypos << std::endl;
			}

			void glfw_scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
			{
				std::cout << "Scroll " << xOffset << " " << xOffset << std::endl;
			}

			static void glfw_error_callback(int error, const char* description)
			{
				fprintf(stderr, "Error: %s\n", description);
			}

			GlfwRenderWindow* m_parent;
			GLFWwindow* m_window;
			int prevMouseState = GLFW_RELEASE;
			double prevMouseX, prevMouseY;
		};

		// Constructor
		GlfwRenderWindow::GlfwRenderWindow(bool debug)
			: RenderWindow(debug)
			, m_pimpl(new impl(this, debug))
		{
		}

		// Destructor
		GlfwRenderWindow::~GlfwRenderWindow()
		{
		}

		bool GlfwRenderWindow::init()
		{
			return m_pimpl->init();
		}

		bool GlfwRenderWindow::createWindow(int width, int height)
		{
			return m_pimpl->createWindow(width, height);
		}

		void GlfwRenderWindow::destroyWindow()
		{
			m_pimpl->destroyWindow();
		}

		void GlfwRenderWindow::terminate() const
		{
			m_pimpl->terminate();
		}

		void GlfwRenderWindow::show()
		{
			m_pimpl->show();
		}

	} // namespace gfx3d
} // namespace spatiumgl
