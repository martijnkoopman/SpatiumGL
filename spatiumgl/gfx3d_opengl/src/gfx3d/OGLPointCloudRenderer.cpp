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

#include <GL/glew.h>

#include "spatiumgl/gfx3d/OGLPointCloudRenderer.hpp"

#include <string>
#include <iostream>

namespace spatiumgl {
	namespace gfx3d {

		OGLPointCloudRenderer::OGLPointCloudRenderer(const PointCloud* pointCloud)
			: OGLRenderer(pointCloud)
		{
			m_valid = true;

			std::string vertexShaderSrc, fragmentShaderSrc;
			if (pointCloud->hasColors())
			{
				vertexShaderSrc =
					"#version 330 core\n"
					"layout (location = 0) in vec3 pos;\n"
					"layout (location = 1) in vec3 color;\n"
					"uniform mat4 viewMatrix;\n"
					"uniform mat4 projectionMatrix;\n"
					"out vec3 vertexColor;\n"
					"void main()\n"
					"{\n"
					"   gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0);\n"
					"   vertexColor = color;\n"
					"}\0";

				fragmentShaderSrc =
					"#version 330 core\n"
					"in vec3 vertexColor;"
					"out vec4 FragColor;\n"
					"void main()\n"
					"{\n"
					"   FragColor = vec4(vertexColor, 1.0);\n"
					"}\n\0";
			}
			else
			{
				vertexShaderSrc =
					"#version 330 core\n"
					"layout (location = 0) in vec3 pos;\n"
					"uniform mat4 viewMatrix;\n"
					"uniform mat4 projectionMatrix;\n"
					"void main()\n"
					"{\n"
					"   gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0);\n"
					"}\n\0";

				fragmentShaderSrc =
					"#version 330 core\n"
					"out vec4 FragColor;\n"
					"void main()\n"
					"{\n"
					"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0);\n"
					"}\n\0";
			}

			// Create shader program with vertex and fragment shader
			m_shaderProgram.setShaderSources(vertexShaderSrc, fragmentShaderSrc);

			// Validate shader program
			std::string errorMessage;
			if (!m_shaderProgram.validate(errorMessage))
			{
				std::cerr << "[ERROR] fragment shader compilation: " << errorMessage << std::endl;
				m_valid = false;
				return;
			}

			// Create vertex buffer object (VBO) and vertex array object (VAO)
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);

			// Bind VAO object first
			glBindVertexArray(m_vao);

			// Bind VBO object
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			// Allocate vertex attributes buffer
			const size_t pointCount = pointCloud->positions().size();
			const size_t pointBufferSize = pointCount * sizeof(double) * 3;
			if (pointCloud->colors().size() == pointCount)
			{
				// Allocate vertex attributes buffer for points + colors
				glBufferData(GL_ARRAY_BUFFER, 2 * pointBufferSize, nullptr, GL_STATIC_DRAW);

				// Fill vertex attributes with positions and colors
				glBufferSubData(GL_ARRAY_BUFFER, 0, pointBufferSize, (void*)pointCloud->positions().data());
				glBufferSubData(GL_ARRAY_BUFFER, pointBufferSize, pointBufferSize, (void*)pointCloud->colors().data());

				// Specify strucutre of a single vertex attribute, and enable
				glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0); // positions
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)(pointBufferSize)); // colors
				glEnableVertexAttribArray(1);
			}
			else
			{
				// Allocate vertex attributes buffer for points
				glBufferData(GL_ARRAY_BUFFER, pointBufferSize, pointCloud->positions().data(), GL_STATIC_DRAW);

				// Specify strucutre of a single vertex attribute, and enable
				glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
				glEnableVertexAttribArray(0);
			}

			// Unbind for now to prevent unintended overwriting
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		OGLPointCloudRenderer::~OGLPointCloudRenderer()
		{
			// TODO: Delete shader?

			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);
		}

		const PointCloud* OGLPointCloudRenderer::pointCloud() const
		{
			return static_cast<const PointCloud*>(m_renderObject);
		}

		void OGLPointCloudRenderer::render(spatiumgl::gfx3d::Camera* camera, double aspect)
		{
			m_shaderProgram.use();

			// Set shader uniform values: view and projection matrix
			const spatiumgl::Matrix4x4 viewMatrix = camera->transform().matrix().inverse();
			int viewMatrixLoc = glGetUniformLocation(m_shaderProgram.shaderProgamId(), "viewMatrix");
			glUniformMatrix4dv(viewMatrixLoc, 1, GL_FALSE, (const double*)viewMatrix.data());

			const spatiumgl::Matrix<SPATIUMGL_PRECISION, 4, 4> projectionMatrix = spatiumgl::Matrix4x4::perspective(camera->fov(), aspect, camera->near(), camera->far());
			int projectionMatrixLoc = glGetUniformLocation(m_shaderProgram.shaderProgamId(), "projectionMatrix");
			glUniformMatrix4dv(projectionMatrixLoc, 1, GL_FALSE, (double*)projectionMatrix.data());

			// Bind vertex array object
			glBindVertexArray(m_vao);

			// Draw
			glDrawArrays(GL_POINTS, 0, pointCloud()->pointCount());
		}

	} // namespace gfx3d
} // namespace spatiumgl
