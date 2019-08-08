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

#include "spatiumglexport.hpp"
#include "RenderWindow.hpp"

namespace spatiumgl
{

class SPATIUMGL_EXPORT GlfwRenderWindow : public RenderWindow
{
public:
	// Constructor
	GlfwRenderWindow();

	// Destructor
	virtual ~GlfwRenderWindow();

	bool init() override;
	bool createWindow(int width, int height) override;
	void destroyWindow() override;
	void terminate() const override;

	void show() override;

protected:
	void draw();
	void processUserInput();
	void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void glfw_error_callback(int error, const char* description);

	GLFWwindow* m_window;

	int prevMouseState = GLFW_RELEASE;
	double prevMouseX, prevMouseY;
};

} // namespace spatiumgl

#endif // SPATIUMGL_GLFWRENDERWINDOW_H