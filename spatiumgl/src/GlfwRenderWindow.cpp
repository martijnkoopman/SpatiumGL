#include "spatiumgl/GlfwRenderWindow.hpp" 

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

namespace spatiumgl
{
	// Constructor
	GlfwRenderWindow::GlfwRenderWindow()
		: m_window(nullptr)
		, m_renderer(nullptr)
		, m_camera(nullptr)
		, prevMouseState(GLFW_RELEASE)
		, prevMouseX(0)
		, prevMouseY(0)
	{
	}


	// Destructor
	GlfwRenderWindow::~GlfwRenderWindow()
	{

	}

	bool GlfwRenderWindow::init()
	{
		// Set error calback function
		glfwSetErrorCallback(&GlfwRenderWindow::glfw_error_callback);

		// Initialize GLFW
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW.\n");
			return false;
		}
		return true;
	}

	bool GlfwRenderWindow::createWindow()
	{
		// Create window with OpenGL context
		m_window = glfwCreateWindow(640, 480, "TinyGL", NULL, NULL);
		if (!m_window)
		{
			fprintf(stderr, "Failed to create window or OpenGL context.\n");

			// Release resources of GLFW
			glfwTerminate();
			return false;
		}

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
		glfwSetFramebufferSizeCallback(m_window, &GlfwRenderWindow::glfw_framebuffer_size_callback);

		// Get current frame buffer size
		//glfwGetFramebufferSize(m_window, frame_buffer_size, frame_buffer_size + 1);

		// Set swap interval of front and back buffer to 1 frame instead of 0 (immediate)
		glfwSwapInterval(1);
	}

	void GlfwRenderWindow::destroyWindow()
	{
		// Destroy window and OpenGL context
		glfwDestroyWindow(m_window);

		m_window = nullptr;
	}

	void GlfwRenderWindow::terminate() const
	{
		glfwTerminate();
	}

	void GlfwRenderWindow::setCamera(Camera* camera)
	{
		m_camera = camera;
	}

	void GlfwRenderWindow::setRenderer(Renderer* renderer)
	{
		m_renderer = renderer;
	}

	void GlfwRenderWindow::show()
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

	void GlfwRenderWindow::draw()
	{
		// Clear color buffer (dark gray)
		glClearColor(0.227f, 0.227f, 0.227f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: Deduce width and height from glViewport

		m_renderer->render(m_camera, (float)640 / (float)480);

		// Swap front and back buffer (front = displayed, back = rendered)
		glfwSwapBuffers(m_window);
	}

	void GlfwRenderWindow::processUserInput()
	{
		// Check keyboard input
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_window, true);
		}

		// Check mouse input
		int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
		double mousePosX, mousePosY;
		glfwGetCursorPos(m_window, &mousePosX, &mousePosY);

		if (state == GLFW_PRESS && prevMouseState == GLFW_PRESS)
		{
			// Get mouse movement vector
			double deltaX = mousePosX - prevMouseX;
			double deltaY = mousePosY - prevMouseY;

			// Get viewport size
			int viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			// Get rotation angles
			float angleX = deltaX * glm::pi<float>() / viewport[2];
			float angleY = deltaY * glm::pi<float>() / viewport[3];

			// Rotate
			glm::mat4 rotationX = glm::rotate(angleX, m_camera->transform().up());
			m_camera->transform().setMatrix(rotationX * m_camera->transform().matrix());
			glm::mat4 rotationY = glm::rotate(angleY, m_camera->transform().right());
			m_camera->transform().setMatrix(rotationY * m_camera->transform().matrix());
			//m_camera->orthogonalizeViewUp();
		}

		prevMouseState = state;
		prevMouseX = mousePosX;
		prevMouseY = mousePosY;
	}

	void GlfwRenderWindow::glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void GlfwRenderWindow::glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}

}