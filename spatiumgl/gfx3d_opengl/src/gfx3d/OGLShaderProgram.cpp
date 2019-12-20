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

#include "spatiumgl/gfx3d/OGLShaderProgram.hpp"

#include <GL/glew.h>

namespace spgl {
namespace gfx3d {

OGLShaderProgram::OGLShaderProgram()
  : m_vertexShaderId(0)
  , m_fragmentShaderId(0)
  , m_geometryShaderId(0)
  , m_shaderProgramId(0)
{}

OGLShaderProgram::OGLShaderProgram(const std::string& vertexShaderSource,
                                   const std::string& fragmentShaderSource,
                                   const std::string& geometryShaderSource)
{
  createShaderProgram(
    vertexShaderSource, fragmentShaderSource, geometryShaderSource);
}

OGLShaderProgram::~OGLShaderProgram()
{
  free();
}

void
OGLShaderProgram::setShaderSources(const std::string& vertexShaderSource,
                                   const std::string& fragmentShaderSource,
                                   const std::string& geometryShaderSource)
{
  free();

  createShaderProgram(
    vertexShaderSource, fragmentShaderSource, geometryShaderSource);
}

bool
OGLShaderProgram::validate(std::string& errorMessage)
{
  errorMessage = "";

  // Validate vertex shader
  int success;
  char infoLog[512];
  glGetShaderiv(m_vertexShaderId, GL_COMPILE_STATUS, &success);
  if (success == 0) {
    glGetShaderInfoLog(m_vertexShaderId, 512, nullptr, infoLog);
    errorMessage = infoLog;
    return false;
  }

  // Validate geometry shader
  if (m_geometryShaderId != 0) {
    glGetShaderiv(m_geometryShaderId, GL_COMPILE_STATUS, &success);
    if (success == 0) {
      glGetShaderInfoLog(m_geometryShaderId, 512, nullptr, infoLog);
      errorMessage = infoLog;
      return false;
    }
  }

  // Validate fragment shader
  glGetShaderiv(m_fragmentShaderId, GL_COMPILE_STATUS, &success);
  if (success == 0) {
    glGetShaderInfoLog(m_fragmentShaderId, 512, nullptr, infoLog);
    errorMessage = infoLog;
    return false;
  }

  // Validate shader program
  glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
  if (success == 0) {
    glGetProgramInfoLog(m_shaderProgramId, 512, nullptr, infoLog);
    errorMessage = infoLog;
    return false;
  }

  return true;
}

void
OGLShaderProgram::use()
{
  glUseProgram(m_shaderProgramId);
}

void
OGLShaderProgram::free()
{
  if (m_shaderProgramId > 0) {
    glDeleteProgram(m_shaderProgramId);
    m_shaderProgramId = 0;
    m_vertexShaderId = 0;
    m_fragmentShaderId = 0;
    m_geometryShaderId = 0;
  }
}

// Protected functions

void
OGLShaderProgram::createShaderProgram(const std::string& vertexShaderSource,
                                      const std::string& fragmentShaderSource,
                                      const std::string& geometryShaderSource)
{
  // Create vertex shader
  m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  const char* vertexShaderSourceStr = vertexShaderSource.c_str();
  glShaderSource(m_vertexShaderId, 1, &vertexShaderSourceStr, nullptr);
  glCompileShader(m_vertexShaderId);

  // Create fragment shader
  m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fragmentShaderSourceStr = fragmentShaderSource.c_str();
  glShaderSource(m_fragmentShaderId, 1, &fragmentShaderSourceStr, nullptr);
  glCompileShader(m_fragmentShaderId);

  // Create geometry shader
  if (!geometryShaderSource.empty()) {
    m_geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
    const char* geometryShaderSourceStr = geometryShaderSource.c_str();
    glShaderSource(m_geometryShaderId, 1, &geometryShaderSourceStr, nullptr);
    glCompileShader(m_geometryShaderId);
  }

  // Create shader program
  m_shaderProgramId = glCreateProgram();
  glAttachShader(m_shaderProgramId, m_vertexShaderId);
  if (m_geometryShaderId != 0) {
    glAttachShader(m_shaderProgramId, m_geometryShaderId);
  }
  glAttachShader(m_shaderProgramId, m_fragmentShaderId);
  glLinkProgram(m_shaderProgramId);

  // Delete unattached shaders
  glDeleteShader(m_vertexShaderId);
  glDeleteShader(m_geometryShaderId);
  glDeleteShader(m_fragmentShaderId);
}

} // namespace gfx3d
} // namespace spgl
