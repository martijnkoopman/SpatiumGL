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
      std::string vertexShaderSrc;
      std::string fragmentShaderSrc;
			if (pointCloud->hasColors())
			{
				vertexShaderSrc =
					"#version 330 core\n"
					"layout (location = 0) in vec3 pos;\n"
					"layout (location = 1) in vec3 color;\n"
					"uniform mat4 model;\n"
					"uniform mat4 view;\n"
					"uniform mat4 projection;\n"
					"out vec3 vertexColor;\n"
					"void main()\n"
					"{\n"
					"   gl_Position = projection * view * model * vec4(pos.xyz, 1.0); \n"
					"   vertexColor = color;\n"
					"}\n\0";

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
				// Shader
				vertexShaderSrc = "#version 330 core\n"
					"layout(location = 0) in vec3 aPos;\n"
					"uniform mat4 model;\n"
					"uniform mat4 view;\n"
					"uniform mat4 projection;\n"
					"void main()\n"
					"{\n"
					"gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
					"}";

				fragmentShaderSrc = "#version 330 core\n"
					"out vec4 FragColor;\n"
					"void main()\n"
					"{\n"
					"FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
					"}";
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

			// Create vertex array object (VAO) and bind
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);

			// Create vertex buffer object (VBO) and bind
			glGenBuffers(1, &m_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			const size_t pointCount = pointCloud->positions().size();
			std::vector<Vector3f> verticesFloat(pointCount);
			for (size_t i = 0; i < pointCount; i++)
				verticesFloat[i] = pointCloud->positions()[i].staticCast<float>();

			// Allocate vertex attributes buffer
			const size_t pointBufferSize = pointCount * sizeof(float) * 3;
			if (pointCloud->colors().size() == pointCount)
			{
				// THESE DOUBLES ARE NOT WORKING.

				std::vector<Vector3f> colorsFloat(pointCount);
				for (size_t i = 0; i < pointCount; i++)
					colorsFloat[i] = pointCloud->colors()[i].staticCast<float>();

				// Allocate vertex attributes buffer for points + colors
				glBufferData(GL_ARRAY_BUFFER, 2 * pointBufferSize, nullptr, GL_STATIC_DRAW);

				// Fill vertex attributes with positions and colors
				glBufferSubData(GL_ARRAY_BUFFER, 0, pointBufferSize, (void*)verticesFloat.data());
				glBufferSubData(GL_ARRAY_BUFFER, pointBufferSize, pointBufferSize, (void*)colorsFloat.data());

				// Specify strucutre of a single vertex attribute, and enable
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr); // positions
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(pointBufferSize)); // colors
				glEnableVertexAttribArray(1);
			}
			else
			{
				// Allocate vertex attributes buffer for points
				glBufferData(GL_ARRAY_BUFFER, pointBufferSize, verticesFloat.data(), GL_STATIC_DRAW);

				// Specify strucutre of a single vertex attribute, and enable
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
				glEnableVertexAttribArray(0);
			}

			// Unbind for now to prevent unintended overwriting
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			m_valid = true;
		}

		OGLPointCloudRenderer::~OGLPointCloudRenderer()
		{
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

			{
				// Set model matrix
				const spatiumgl::Matrix4 modelMatrix = m_renderObject->transform().matrix();
				int modelMatrixLoc = glGetUniformLocation(m_shaderProgram.shaderProgamId(), "model");
				const spatiumgl::Matrix4f modelMatrixF = modelMatrix.staticCast<float>();
				glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrixF.data());
			}

			{
				// Set view matrix
				const spatiumgl::Matrix4 viewMatrix = camera->transform().matrix().inverse(); // MAY THROW EXCEPTION!
				int viewMatrixLoc = glGetUniformLocation(m_shaderProgram.shaderProgamId(), "view");
				const spatiumgl::Matrix4f viewMatrixF = viewMatrix.staticCast<float>();
				glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrixF.data());
			}

			{
				// Set projection matrix
				const spatiumgl::Matrix4 projectionMatrix = camera->projectionMatrix(aspect);
				int projectionMatrixLoc = glGetUniformLocation(m_shaderProgram.shaderProgamId(), "projection");
				const spatiumgl::Matrix4f projectionMatrixF = projectionMatrix.staticCast<float>();
				glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, projectionMatrixF.data());
			}

			// Bind vertex array object
			glBindVertexArray(m_vao);

			// Draw
			glDrawArrays(GL_POINTS, 0, pointCloud()->pointCount());

			// Unbind vertex array object
			glBindVertexArray(0);
		}

	} // namespace gfx3d
} // namespace spatiumgl
