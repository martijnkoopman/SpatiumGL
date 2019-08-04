#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::lookat
#include <glm/gtx/string_cast.hpp>

#include <spatiumgl/PointCloud.hpp>
#include <spatiumgl/PointCloudRenderer.hpp>
#include <spatiumgl/Camera.hpp>

#include <spatiumgl/GlfwRenderWindow.hpp>

#include <stdio.h> // fprintf

void opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int main(int argc, char *argv[])
{
	// Optional: request OpenGL context version with glfwWindowHint()

	spatiumgl::GlfwRenderWindow renderWindow;
	renderWindow.init();

	// Create window with OpenGL context
	if (!renderWindow.createWindow(640, 480))
	{
		fprintf(stderr, "Failed to create window or OpenGL context.\n");

		// Release resources of GLFW
		renderWindow.terminate();
		return 1;
	}

	// Print OpenGL version in use
	fprintf(stderr, "OpenGL version: %s\n", glGetString(GL_VERSION));
	fprintf(stderr, "GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Initialize GLEW extension loader library
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glewError));

		// Exit
		renderWindow.terminate();
		return 1;
	}

	// Capture OpenGL debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(opengl_error_callback, NULL);

	// BEGIN: OpenGL rendering stuff...
	
	spatiumgl::Camera *camera = new spatiumgl::Camera(glm::radians(45.0f), 1.0f, 100.0f);
	camera->lookAt(glm::vec3(0, -10, 0), glm::vec3(0, 0, 0), glm::vec3(0,0,1));
	//std::cout << glm::to_string(camera->transform().matrix()) << std::endl;
	//std::cout << "Camera pos: " << camera->transform().position().x << " " << camera->transform().position().y << " " << camera->transform().position().z << std::endl;
	//std::cout << "Camera up: " << camera->transform().up().x << " " << camera->transform().up().y << " " << camera->transform().up().z << std::endl;
	//std::cout << "Camera right: " << camera->transform().right().x << " " << camera->transform().right().y << " " << camera->transform().right().z << std::endl;
	//std::cout << "Camera back: " << camera->transform().back().x << " " << camera->transform().back().y << " " << camera->transform().back().z << std::endl;
	renderWindow.setCamera(camera);

	// Create point cloud
	std::vector<glm::vec3> positions = { {0.0f,  0.0f, 1.0f },
										{ 1.0f,  0.0f, -1.0f },
										{ -1.0f, 0.0f, -1.0f } };
	std::vector<glm::vec3> colors = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};
	spatiumgl::PointCloud* pointcloud = new spatiumgl::PointCloud(positions, colors);
	
	// Create point cloud renderer
	spatiumgl::PointCloudRenderer* renderer = new spatiumgl::PointCloudRenderer(pointcloud);
	if (!renderer->isValid())
	{
		// Exit
		renderWindow.terminate();
		return 1;
	}

	renderWindow.setRenderer(renderer);
	renderWindow.show();

	renderWindow.destroyWindow();
	// Release resources
	renderWindow.terminate();

	delete renderer;
	delete pointcloud;

	return 0;
}

void opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	char* typeStr = "unknown";
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

	char* severityStr = "unknown";
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

	fprintf(stderr, "GL CALLBACK: type = %s, severity = %s, message = %s\n",
		typeStr, severityStr, message);
}