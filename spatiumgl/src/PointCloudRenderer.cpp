#include "spatiumgl/PointCloudRenderer.hpp"

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <string>

namespace spatiumgl {

	PointCloudRenderer::PointCloudRenderer(const PointCloud* pointCloud)
		: Renderer(pointCloud)
	{
		m_valid = true;

		const char* vertexShaderSrc, * fragmentShaderSrc;
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

		// Create vertex shader
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
		glCompileShader(vertexShader);

		// Validate vertex shader
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			fprintf(stderr, "[ERROR] Vetrex shader compilation: %s\n", infoLog);

			m_valid = false;
			return;
		}

		// Create fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
		glCompileShader(fragmentShader);

		// Validate fragment shader
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			fprintf(stderr, "[ERROR] fragment shader compilation: %s\n", infoLog);

			m_valid = false;
			return;
		}

		// Create shader program
		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);

		// Validate shader program
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
			fprintf(stderr, "[ERROR] shader program linking: %s\n", infoLog);

			m_valid = false;
			return;
		}

		// Delete unattached shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Create vertex buffer object (VBO) and vertex array object (VAO)
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		// Bind VAO object first
		glBindVertexArray(m_vao);

		// Bind VBO object
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		// Allocate vertex attributes buffer
		const size_t pointCount = pointCloud->positions().size();
		const size_t pointBufferSize = pointCount * sizeof(float) * 3;
		if (pointCloud->colors().size() == pointCount)
		{
			// Allocate vertex attributes buffer for points + colors
			glBufferData(GL_ARRAY_BUFFER, 2 * pointBufferSize, NULL, GL_STATIC_DRAW);

			// Fill vertex attributes with positions and colors
			glBufferSubData(GL_ARRAY_BUFFER, 0, pointBufferSize, (void*)pointCloud->positions().data());
			glBufferSubData(GL_ARRAY_BUFFER, pointBufferSize, pointBufferSize, (void*)pointCloud->colors().data());

			// Specify strucutre of a single vertex attribute, and enable
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(pointBufferSize)); // colors
			glEnableVertexAttribArray(1);
		}
		else
		{
			// Allocate vertex attributes buffer for points
			glBufferData(GL_ARRAY_BUFFER, pointBufferSize, pointCloud->positions().data(), GL_STATIC_DRAW);

			// Specify strucutre of a single vertex attribute, and enable
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		// Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	PointCloudRenderer::~PointCloudRenderer()
	{
		// TODO: Delete shader?

		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}

	const PointCloud* PointCloudRenderer::pointCloud() const
	{
		return static_cast<const PointCloud*>(m_renderObject);
	}

	void PointCloudRenderer::render(spatiumgl::Camera* camera, float aspect)
	{
		// Use shader program
		glUseProgram(m_shaderProgram);

		// Set shader uniform values 
		glm::mat4 viewMatrix = glm::inverse(camera->transform().matrix());
		int viewMatrixLoc = glGetUniformLocation(m_shaderProgram, "viewMatrix");
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		glm::mat4 projectionMatrix = glm::perspective(camera->fov(), aspect, camera->near(), camera->far());
		int projectionMatrixLoc = glGetUniformLocation(m_shaderProgram, "projectionMatrix");
		glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		// Bind vertex array object
		glBindVertexArray(m_vao);

		// Draw
		glDrawArrays(GL_TRIANGLES, 0, pointCloud()->pointCount() / 3);
	}

} // namespace spatiumgl