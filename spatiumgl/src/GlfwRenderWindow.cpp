#include "spatiumgl/GlfwRenderWindow.hpp" 

#include <GL/glew.h> // Include GLEW *always* just before GLFW.
#include <GLFW/glfw3.h> // GLFWwindow

#include <iostream>

namespace spatiumgl
{
	class GlfwRenderWindow::impl
	{
	public:
		// Constructor
		impl(GlfwRenderWindow *parent, bool debug=false)
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

			// Initialize GLFW
			if (!glfwInit())
			{
				fprintf(stderr, "Failed to initialize GLFW.\n");
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

			// Capture frame buffer resize event (is not equal to window size)
			glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* win, int w, int h)
				{
					static_cast<impl*>(glfwGetWindowUserPointer(win))->glfw_framebuffer_size_callback(win, w, h);
				});
			//&GlfwRenderWindow::glfw_framebuffer_size_callback);

			// Get current frame buffer size
			glfwGetFramebufferSize(m_window, &m_parent->m_framebufferSize[0], &m_parent->m_framebufferSize[1]); // m_framebufferSize.data(), m_framebufferSize.data() + 1);

			// Set swap interval of front and back buffer to 1 frame instead of 0 (immediate)
			glfwSwapInterval(1);
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
		, m_pimpl(std::make_unique<impl>(this, debug))
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

}