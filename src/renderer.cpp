
#include <texture.hpp>
#include <exception.hpp>
#include <renderer.hpp>
#include <fps.hpp>
#include <shader.hpp>
#include <helper.hpp>
#include <game.hpp>

#include <array>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE

namespace opengles_workspace
{

	std::vector<std::vector<int>> game_matrix;
	texture texture_instance;
	fps fps_instance;
	shader shader_instance;
	helper helper_instance;
	game game_state;

	GLFWRenderer::GLFWRenderer(std::shared_ptr<Context> context)
		: mContext(std::move(context)),
		  shaderProgram(glCreateProgram())
	{

		glViewport(0, 0, 800, 800);

		vertexShader = shader_instance.LoadShader(vShaderStr, GL_VERTEX_SHADER);
		fragmentShader = shader_instance.LoadShader(fShaderStr, GL_FRAGMENT_SHADER);
		LinkProgram();

		helper_instance.ReadNumbersFromFile(filename, rows_from_file_, columns_from_file_);
		game_matrix = game_state.initializeMatrix(rows_from_file_, columns_from_file_);
		lower_limit_reached_ = false;

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void GLFWRenderer::LinkProgram()
	{

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

	}

	void GLFWRenderer::render()
	{

		ClearBackBuffer();
		DrawWithTexture(vVertices_single_square_vector, brick_texture_);

		glfwSwapBuffers(window());
	}

	void GLFWRenderer::ClearBackBuffer()
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLFWRenderer::DrawWithTexture(std::vector<GLfloat> &vertices,
									   char *textureFileLoc)
	{

		texture_instance = texture(textureFileLoc);
		texture_instance.LoadTexture();

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(vertices[0]), (void *)(sizeof(vertices[0]) * 3));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// GL code begin

		glUseProgram(shaderProgram);

		texture_instance.UseTexture();

		glBindVertexArray(VAO);

		glDrawArrays(GL_QUADS, 0, kVerticesPerSquare * (nr_squares_ / 2 + 1)); // added an extra 1 in case nr_squares_ is odd number

		// Delete all the objects we've created
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
	}

	void GLFWRenderer::IncrementYCoordinate(std::vector<GLfloat> &vertices, float offset)
	{
		vertices[1] += offset;
		vertices[6] += offset;
		vertices[11] += offset;
		vertices[16] += offset;
	}

	void GLFWRenderer::DecrementYCoordinate(std::vector<GLfloat> &vertices, float offset)
	{
		vertices[1] -= offset;
		vertices[6] -= offset;
		vertices[11] -= offset;
		vertices[16] -= offset;
	}

	bool GLFWRenderer::CheckProgramStatus(GLuint programId)
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

	bool GLFWRenderer::CheckUniformLocationError(GLint location, const char *variableName)
	{
		if (location == -1)
		{
			std::cerr << "Error: Uniform variable '" << variableName
					  << "' not found or inactive." << std::endl;
			return false;
		}
		return true;
	}

	void printMatrix(const std::vector<std::vector<int>> &matrix)
	{
		// Get the number of rows and columns in the matrix
		int rows = matrix.size();
		int columns = matrix[0].size();

		// Print each element of the matrix
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	
	bool GLFWRenderer::poll()
	{
		long long current_time = fps_instance.GetCurrentTimeMillis();
		float elapsed_time = (current_time - fps_instance.GetStartTime()) / 1000.0f;
		int target_fps = 1;

		if (elapsed_time >= 1.0f / target_fps)
		{

			render();

			if (game_state.CheckLastRowForOne(game_matrix))
			{
				lower_limit_reached_ = true;
			}
			else if (game_state.CheckFirstRowForOne(game_matrix))
			{
				lower_limit_reached_ = false;
			}

			if (lower_limit_reached_)
			{
				IncrementYCoordinate(vVertices_single_square_vector, 0.5f); 
				game_state.MoveOneUp(game_matrix); // 
				//std::cout<<"if" << std::endl;
				//printMatrix(myMatrix);
			}
			else
			{
				DecrementYCoordinate(vVertices_single_square_vector, 0.5f);
				game_state.MoveOneDown(game_matrix);
				//std::cout<<"else" << std::endl;
				//printMatrix(myMatrix);
			}

			fps_instance.SetStartTime(current_time);
		}

		return true;
	}

} // namespace opengles_workspace