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

namespace spatiumgl {
	namespace gfx3d {

		OGLShaderProgram::OGLShaderProgram(const std::string& vertexShaderSource,
			const std::string& fragmentShaderSource)
		{
			createShaderProgram(vertexShaderSource, fragmentShaderSource);
		}

		void OGLShaderProgram::setShaderSources(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
		{
			createShaderProgram(vertexShaderSource, fragmentShaderSource);
		}

		bool OGLShaderProgram::validate(std::string& errorMessage)
		{
			errorMessage = "";

			// Validate vertex shader
			int success;
			char infoLog[512];
			glGetShaderiv(m_vertexShaderId, GL_COMPILE_STATUS, &success);
			if (success == 0)
			{
        glGetShaderInfoLog(m_vertexShaderId, 512, nullptr, infoLog);
				errorMessage = infoLog;
				return false;
			}

			// Validate fragment shader
			glGetShaderiv(m_fragmentShaderId, GL_COMPILE_STATUS, &success);
			if (success == 0)
			{
        glGetShaderInfoLog(m_fragmentShaderId, 512, nullptr, infoLog);
				errorMessage = infoLog;
				return false;
			}

			// Validate shader program
			glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
			if (success == 0)
			{
        glGetProgramInfoLog(m_shaderProgramId, 512, nullptr, infoLog);
				errorMessage = infoLog;
				return false;
			}

			return true;
		}

		void OGLShaderProgram::use()
		{
			glUseProgram(m_shaderProgramId);
		}

		// Protected functions

		void OGLShaderProgram::createShaderProgram(const std::string& vertexShaderSource,
			const std::string& fragmentShaderSource)
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

			// Create shader program
			m_shaderProgramId = glCreateProgram();
			glAttachShader(m_shaderProgramId, m_vertexShaderId);
			glAttachShader(m_shaderProgramId, m_fragmentShaderId);
			glLinkProgram(m_shaderProgramId);

			// Delete unattached shaders
			glDeleteShader(m_vertexShaderId);
			glDeleteShader(m_fragmentShaderId);
		}
		
	} // namespace gfx3d
} // namespace spatiumgl
