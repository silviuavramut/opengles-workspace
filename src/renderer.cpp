#include <renderer.hpp>
#include <exception.hpp>

#include <memory>
#include <optional>
#include <cassert>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace opengles_workspace
{

	// Shader Sources
	const char *vShaderStr =
		"#version 300 es                          \n"
		"layout(location = 0) in vec4 vPosition;  \n"
		"void main()                              \n"
		"{                                        \n"
		"   gl_Position = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);              \n"
		"}                                        \n";

	const char *fShaderStr =
		"#version 300 es                              \n"
		"precision mediump float;                       \n"
		"uniform vec4 uniformColor;                        \n"
		"out vec4 FragColor;                          \n"
		"void main()                                  \n"
		"{                                            \n"
		"   FragColor = uniformColor;  \n"
		"}                                            \n";

	std::vector<GLfloat> vVertices_white{};
	std::vector<GLfloat> vVertices_blue{};
	size_t nr_squares;
	const size_t vertices_per_square = 4;

	GLFWRenderer::GLFWRenderer(std::shared_ptr<Context> context)
		: mContext(std::move(context))
	{
	}

	bool GLFWRenderer::checkProgramStatus(GLuint programId)
	{
		GLint linked;
		glGetProgramiv(programId, GL_LINK_STATUS, &linked);

		if (!linked)
		{
			GLint infoLength = 0;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLength);

			if (infoLength > 1)
			{
				char *infoLog = new char[infoLength];
				glGetProgramInfoLog(programId, infoLength, NULL, infoLog);
				std::cerr << "Error linking program: " << infoLog << std::endl;
				delete[] infoLog;
			}

			return false;
		}

		return true;
	}

	bool GLFWRenderer::checkUniformLocationError(GLint location, const char *variableName)
	{
		if (location == -1)
		{
			std::cerr << "Error: Uniform variable '" << variableName << "' not found or inactive." << std::endl;
			return false;
		}
		return true;
	}

	void GLFWRenderer::render()
	{

		std::vector<GLfloat> white_color = {1.0f, 1.0f, 1.0f, 1.0f};
		std::vector<GLfloat> blue_color = {0.0f, 0.0f, 1.0f, 1.0f};
		clear_back_buffer();
		calculate_square_values(vVertices_white, vVertices_blue);
		draw(vVertices_white, white_color);
		draw(vVertices_blue, blue_color);

		glfwSwapBuffers(window());
	}
	void GLFWRenderer::clear_back_buffer()
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
	}

	bool GLFWRenderer::readNumbersFromFile(const std::string &filename, int &num1, int &num2)
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			std::cerr << "Error: Unable to open file " << filename << std::endl;
			return false;
		}

		std::string line;
		if (std::getline(file, line))
		{
			std::istringstream iss(line);
			char comma;
			if (iss >> num1 >> comma >> num2)
			{
				if (comma != ',')
				{
					std::cerr << "Error: Expected comma delimiter" << std::endl;
					return false;
				}
				return true;
			}
			else
			{
				std::cerr << "Error: Unable to read numbers from line" << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "Error: File is empty" << std::endl;
			return false;
		}
	}

	void GLFWRenderer::calculate_square_values(std::vector<GLfloat> &vec, std::vector<GLfloat> &vec2)
	{
		std::string filename = "/home/silviu/opengl-silviu/opengles-workspace/src/numbers.txt";
		GLfloat x = -1.0f;
		GLfloat y = 1.0f;
		GLfloat z = 0.0f;
		int rows_from_file;
		int columns_from_file;
		readNumbersFromFile(filename,rows_from_file,columns_from_file);
		GLfloat length_value_row = 2.0f / columns_from_file;
		GLfloat length_value_column = 2.0f / rows_from_file;
		nr_squares = rows_from_file * columns_from_file;
		const int nr_rows = nr_squares / rows_from_file;
		const int nr_columns = nr_squares / columns_from_file;

		for (int i = 1; i <= nr_columns; i++)
		{
			for (int j = 1; j <= nr_rows; j++)
			{
				GLfloat bottom_left_x = x;
				GLfloat bottom_left_y = y - length_value_column;
				GLfloat bottom_left_z = z;

				GLfloat bottom_right_x = x + length_value_row;
				GLfloat bottom_right_y = y - length_value_column;
				GLfloat bottom_right_z = z;

				GLfloat top_right_x = x + length_value_row;
				GLfloat top_right_y = y;
				GLfloat top_right_z = z;

				GLfloat top_left_x = x;
				GLfloat top_left_y = y;
				GLfloat top_left_z = z;

				if ((i % 2 != 0 && j % 2 != 0) || (i % 2 == 0 && j % 2 == 0))
				{
					vec.push_back(bottom_left_x);
					vec.push_back(bottom_left_y);
					vec.push_back(bottom_left_z);
					vec.push_back(bottom_right_x);
					vec.push_back(bottom_right_y);
					vec.push_back(bottom_right_z);
					vec.push_back(top_right_x);
					vec.push_back(top_right_y);
					vec.push_back(top_right_z);
					vec.push_back(top_left_x);
					vec.push_back(top_left_y);
					vec.push_back(top_left_z);
				}
				else
				{
					vec2.push_back(bottom_left_x);
					vec2.push_back(bottom_left_y);
					vec2.push_back(bottom_left_z);
					vec2.push_back(bottom_right_x);
					vec2.push_back(bottom_right_y);
					vec2.push_back(bottom_right_z);
					vec2.push_back(top_right_x);
					vec2.push_back(top_right_y);
					vec2.push_back(top_right_z);
					vec2.push_back(top_left_x);
					vec2.push_back(top_left_y);
					vec2.push_back(top_left_z);
				}

				x = x + length_value_row;
			}

			x = -1.0f;
			y = y - length_value_column;
		}
	}

	void GLFWRenderer::draw(std::vector<GLfloat> &vertices, std::vector<GLfloat> color)
	{

		GLuint vertexShader, fragmentShader, shaderProgram;

		// Initialize the shaders and the program
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		shaderProgram = glCreateProgram();

		glShaderSource(vertexShader, 1, &vShaderStr, NULL);
		glCompileShader(vertexShader);

		glShaderSource(fragmentShader, 1, &fShaderStr, NULL);
		glCompileShader(fragmentShader);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Create reference containers for VAO and VBO
		GLuint VAO, VBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		// Enable the Vertex Attribute so that OpenGL knows to use it
		glEnableVertexAttribArray(0);
		// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// GL code begin

		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);

		GLint colorLoc = glGetUniformLocation(shaderProgram, "uniformColor");
		if (!checkUniformLocationError(colorLoc, "uniformColor"))
		{
			// Handle the error
		}
		glUniform4f(colorLoc, color[0], color[1], color[2], color[3]);

		glBindVertexArray(VAO);

		glDrawArrays(GL_QUADS, 0, vertices_per_square * (nr_squares / 2 + 1)); // added an extra 1 in case nr_squares is odd number

		// Delete all the objects we've created
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
	}
	bool GLFWRenderer::poll()
	{
		if (glfwWindowShouldClose(window()))
		{
			return false;
		}
		return true;
	}

}