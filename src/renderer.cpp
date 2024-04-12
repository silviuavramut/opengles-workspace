
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


		cell_width = 2.0f / columns_from_file_;
		cell_height = 2.0f /  rows_from_file_;

		square_vertices_vector = helper_instance.CalculateSquareVertices(game_matrix,cell_width,cell_height);


		horizontal_offset_ = 2.0f / rows_from_file_;
		vertical_offset_ = 2.0f / columns_from_file_;

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
		DrawWithTexture(square_vertices_vector, brick_texture_);

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
		glBufferData(GL_ARRAY_BUFFER, square_vertices_vector.size() * sizeof(float), square_vertices_vector.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(square_vertices_vector[0]), (void *)(sizeof(square_vertices_vector[0]) * 3));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// GL code begin

		glUseProgram(shaderProgram);

		texture_instance.UseTexture();

		glBindVertexArray(VAO);

		glDrawArrays(GL_QUADS, 0, kVerticesPerSquare * 100 ); 

		// Delete all the objects we've created
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
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
		std::cout << "game matrix\n";

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
	void printVector(const std::vector<GLfloat> &vec)
	{
		std::cout << "Vector Contents:" << std::endl;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			std::cout << "[" << i << "]: " << vec[i];
			if ((i + 1) % 20 == 0 || i == vec.size() - 1)
			{
				std::cout << std::endl;
			}
			else
			{
				std::cout << " ";
			}
		}
	}

	void GLFWRenderer::AppendVertices(std::vector<GLfloat> &vertices, const std::vector<GLfloat> &newVertices)
	{
		// Iterate through newVertices and append each element to vertices
		for (float vertex : newVertices)
		{
			vertices.push_back(vertex);
		}
	}

	bool hasRowFilledWithOnes(const std::vector<std::vector<int>> &matrix)
	{
		for (const auto &row : matrix)
		{
			bool allOnes = true;
			for (int elem : row)
			{
				if (elem != 1)
				{
					allOnes = false;
					break;
				}
			}
			if (allOnes)
			{
				return true;
			}
		}
		return false;
	}

	// Function to shift rows down if there's a row filled with 1's in the matrix
	void removeAndShiftRowsWithOnes(std::vector<std::vector<int>> &matrix)
	{
		int numRows = matrix.size();
		for (int i = numRows - 1; i >= 0; --i)
		{
			bool allOnes = true;
			for (int elem : matrix[i])
			{
				if (elem != 1)
				{
					allOnes = false;
					break;
				}
			}
			if (allOnes)
			{
				matrix.erase(matrix.begin() + i);
				matrix.push_back(std::vector<int>(matrix[0].size(), 0));
			}
		}
	}

	bool GLFWRenderer::poll()
	{
		long long current_time = fps_instance.GetCurrentTimeMillis();
		float elapsed_time = (current_time - fps_instance.GetStartTime()) / 1000.0f;
		int target_fps = 15;

		if (elapsed_time >= 1.0f / target_fps)
		{
			game_state.MoveOneDown(game_matrix);
			square_vertices_vector = helper_instance.CalculateSquareVertices(game_matrix,cell_width,cell_height);


			if (game_state.HitsLowerBoundary(game_matrix))
			{
				game_state.TransformBoundary(game_matrix);
				game_state.AddNewTwo(game_matrix);
			}


			render();
			fps_instance.SetStartTime(current_time);
		}

		return true;
	}

} // namespace opengles_workspace