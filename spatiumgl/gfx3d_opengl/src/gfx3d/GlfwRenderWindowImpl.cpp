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

#include "GlfwRenderWindowImpl.hpp"

#include <GL/glew.h>    // Include GLEW *always* just before GLFW.
#include <GLFW/glfw3.h> // GLFWwindow

#include <iostream>
#include <string>

namespace spgl {
namespace gfx3d {

static void
opengl_error_callback(GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      const GLchar* message,
                      const void* userParam)
{
  std::string typeStr("unknown");
  switch (type) {
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
  switch (severity) {
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

  std::cerr << "GL CALLBACK: type = " << typeStr
            << ", severity = " << severityStr << ", message = " << message
            << std::endl;
}

// Constructor
GlfwRenderWindowImpl::GlfwRenderWindowImpl(GlfwRenderWindow* parent, bool debug)
  : m_parent(parent)
  , m_window(nullptr)
  , m_drawTime(0)
  , prevMouseState(GLFW_RELEASE)
  , prevMouseX(0)
  , prevMouseY(0)
{}

bool
GlfwRenderWindowImpl::init()
{
  // Set error calback function
  glfwSetErrorCallback(&GlfwRenderWindowImpl::glfw_error_callback);

  // Initialize GLFW (After this always terminate)
  if (!glfwInit()) {
    return false;
  }

  return true;
}

bool
GlfwRenderWindowImpl::createWindow(int width, int height)
{
  // Create window with OpenGL context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  m_window = glfwCreateWindow(
    width, height, "SpatiumGL Render Window", nullptr, nullptr);
  if (!m_window) {
    std::cerr << "Failed to create window or OpenGL context." << std::endl;

    // Release resources of GLFW
    glfwTerminate();
    return false;
  }
  glfwSetWindowUserPointer(m_window, this);

  // Make OpenGL context of window current
  glfwMakeContextCurrent(m_window);

  // Initialize GLEW extension loader library
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    std::cerr << "Error: " << glewGetErrorString(glewError) << std::endl;

    // Exit
    glfwTerminate();
    return false;
  }

  // Enable depth buffer
  glEnable(GL_DEPTH_TEST);

  // Print OpenGL version in use
  std::cout << "OpenGL version: "
            << reinterpret_cast<char const*>(glGetString(GL_VERSION))
            << std::endl;
  std::cout << "GLSL version: "
            << reinterpret_cast<char const*>(
                 glGetString(GL_SHADING_LANGUAGE_VERSION))
            << std::endl;

  // Capture OpenGL debug output
  if (m_parent->m_debug) {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(opengl_error_callback, nullptr);
  }

  // Capture frame buffer resize event (is not equal to window size)
  glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* win, int w, int h) {
    static_cast<GlfwRenderWindowImpl*>(glfwGetWindowUserPointer(win))
      ->glfw_framebuffer_size_callback(win, w, h);
  });

  // Get current frame buffer size
  glfwGetFramebufferSize(
    m_window, &m_parent->m_framebufferSize[0], &m_parent->m_framebufferSize[1]);

  // Set swap interval of front and back buffer to 1 frame instead of 0
  // (immediate)
  glfwSwapInterval(1);

  // Capture user input events

  // Input event: mouse button
  glfwSetMouseButtonCallback(
    m_window, [](GLFWwindow* win, int but, int act, int mod) {
      static_cast<GlfwRenderWindowImpl*>(glfwGetWindowUserPointer(win))
        ->glfw_mouse_button_callback(win, but, act, mod);
    });

  // Input event: cursor position
  glfwSetCursorPosCallback(m_window, [](GLFWwindow* win, double x, double y) {
    static_cast<GlfwRenderWindowImpl*>(glfwGetWindowUserPointer(win))
      ->glfw_cursor_pos_callback(win, x, y);
  });

  // Input event: scroll
  glfwSetScrollCallback(
    m_window, [](GLFWwindow* win, double xOff, double yOff) {
      static_cast<GlfwRenderWindowImpl*>(glfwGetWindowUserPointer(win))
        ->glfw_scroll_callback(win, xOff, yOff);
    });

  // Input event: keys
  glfwSetKeyCallback(
    m_window, [](GLFWwindow* win, int key, int scan, int act, int mod) {
      static_cast<GlfwRenderWindowImpl*>(glfwGetWindowUserPointer(win))
        ->glfw_key_callback(win, key, scan, act, mod);
    });

  return true;
}

void
GlfwRenderWindowImpl::destroyWindow()
{
  // Destroy window and OpenGL context
  glfwDestroyWindow(m_window);

  m_window = nullptr;
}

void
GlfwRenderWindowImpl::terminate() const
{
  glfwTerminate();
}

void
GlfwRenderWindowImpl::show()
{
  // Keep running as long as window shouldn't be closed
  while (!glfwWindowShouldClose(m_window)) {
    // Draw frame
    draw();

    // Process events
    glfwPollEvents();
  }
}

// Protected

void
GlfwRenderWindowImpl::draw()
{
  // Compute delta time since last draw
  const double drawTime = glfwGetTime();
  const double deltaTime = drawTime - m_drawTime;
  m_drawTime = drawTime;

  // Trigger all animators
  for (Animator* animator : m_parent->m_animators) {
    animator->animate(deltaTime);
  }

  // Clear color buffer (dark gray)
  glClearColor(0.227f, 0.227f, 0.227f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Trigger all renderers
  for (Renderer* renderer : m_parent->m_renderers) {
    renderer->render(m_parent->m_camera, m_parent->m_framebufferSize);
  }

  // Swap front and back buffer (front = displayed, back = rendered)
  glfwSwapBuffers(m_window);
}

// GLFW callback functions:

void
GlfwRenderWindowImpl::glfw_framebuffer_size_callback(GLFWwindow* window,
                                                     int width,
                                                     int height)
{
  // Store current viewport size
  m_parent->m_framebufferSize[0] = width;
  m_parent->m_framebufferSize[1] = height;

  // Set viewport size
  glViewport(0, 0, width, height);

  // Draw during window resize
  draw();
}

void
GlfwRenderWindowImpl::glfw_mouse_button_callback(GLFWwindow* window,
                                                 int button,
                                                 int action,
                                                 int mods)
{
  if (m_parent->m_interactor != nullptr) {

    enum RenderWindowInteractor::MouseButton b;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      b = RenderWindowInteractor::MouseButton::MOUSE_BUTTON_LEFT;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
      b = RenderWindowInteractor::MouseButton::MOUSE_BUTTON_RIGHT;
    } else // GLFW_MOUSE_BUTTON_MIDDLE
    {
      b = RenderWindowInteractor::MouseButton::MOUSE_BUTTON_MIDDLE;
    }

    if (action == GLFW_PRESS) {
      m_parent->m_interactor->OnMouseButtonPressed(b, 0, 0);
    } else {
      m_parent->m_interactor->OnMouseButtonReleased(b, 0, 0);
    }

    draw();
  }
}

void
GlfwRenderWindowImpl::glfw_cursor_pos_callback(GLFWwindow* window,
                                               double xpos,
                                               double ypos)
{
  if (m_parent->m_interactor != nullptr) {
    double deltaX = xpos - prevMouseX;
    double deltaY = ypos - prevMouseY;
    prevMouseX = xpos;
    prevMouseY = ypos;
    m_parent->m_interactor->OnMouseMoved(deltaX, deltaY);

    draw();
  }
}

void
GlfwRenderWindowImpl::glfw_scroll_callback(GLFWwindow* window,
                                           double xOffset,
                                           double yOffset)
{
  if (m_parent->m_interactor != nullptr) {
    m_parent->m_interactor->OnMouseWheelScrolled(yOffset);

    draw();
  }
}

void
GlfwRenderWindowImpl::glfw_key_callback(GLFWwindow* window,
                                        int key,
                                        int scancode,
                                        int action,
                                        int mods)
{
  std::cout << "Key " << key << " " << scancode << " " << action << " " << mods
            << std::endl;
}

void
GlfwRenderWindowImpl::glfw_error_callback(int error, const char* description)
{
  std::cerr << "Error: " << std::string(description) << std::endl;
}
} // namespace gfx3d
} // namespace spgl
