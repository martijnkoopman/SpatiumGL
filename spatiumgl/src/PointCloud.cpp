#include "spatiumgl/PointCloud.hpp"

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <string>

namespace spatiumgl {

	PointCloud::PointCloud(const std::vector<float> &positions, const std::vector<float> &colors)
	: m_shaderProgram(0)
	, m_vao(0)
	, m_vbo(0)
	, m_valid(true)
	, m_pointCount(positions.size())
  {
		const char *vertexShaderSrc, *fragmentShaderSrc;
		if (colors.size() == positions.size())
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
		if (colors.size() == positions.size())
		{
			// Allocate vertex attributes buffer
			glBufferData(GL_ARRAY_BUFFER, (positions.size() + colors.size()) * sizeof(float), NULL, GL_STATIC_DRAW);

			// Fill vertex attributes with positions and colors
			glBufferSubData(GL_ARRAY_BUFFER, 0, positions.size() * sizeof(float), (void*)positions.data());
			glBufferSubData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), colors.size() * sizeof(float), (void*)colors.data());

			// Specify strucutre of a single vertex attribute, and enable
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(positions.size() * sizeof(float))); // colors
			glEnableVertexAttribArray(1);
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

			// Specify strucutre of a single vertex attribute, and enable
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		// Unbinc
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	PointCloud::~PointCloud()
	{
		// TODO: Delete shader?

		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}

	bool PointCloud::isValid() const
	{
		return m_valid;
	}

	void PointCloud::render(spatiumgl::Camera *camera, float aspect)
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
		glDrawArrays(GL_TRIANGLES, 0, m_pointCount / 3);
	}

} // namespace spatiumgl