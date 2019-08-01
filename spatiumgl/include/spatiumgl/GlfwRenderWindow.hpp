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

#ifndef SPATIUMGL_GLFWRENDERWINDOW_H
#define SPATIUMGL_GLFWRENDERWINDOW_H

#include <GL/glew.h> // Include GLEW *always* just before GLFW.
#include <GLFW/glfw3.h> // GLFWwindow

#include "Camera.hpp"
#include "Renderer.hpp"
#include "spatiumglexport.h"

namespace spatiumgl
{

class SPATIUMGL_EXPORT GlfwRenderWindow
{
public:
	// Constructor
	GlfwRenderWindow();

	// Destructor
	virtual ~GlfwRenderWindow();

	bool init();
	bool createWindow();
	void destroyWindow();
	void terminate() const;

	void setCamera(Camera* camera);
	void setRenderer(Renderer* renderer);

	void show();

protected:
	void draw();
	void processUserInput();
	static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void glfw_error_callback(int error, const char* description);

	GLFWwindow* m_window ;

	Renderer* m_renderer;
	Camera* m_camera;

	int prevMouseState = GLFW_RELEASE;
	double prevMouseX, prevMouseY;
};

} // namespace spatiumgl

#endif // SPATIUMGL_GLFWRENDERWINDOW_H