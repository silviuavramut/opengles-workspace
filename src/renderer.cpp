
#include <texture.hpp>
#include <exception.hpp>
#include <renderer.hpp>
#include <fps.hpp>
#include <shader.hpp>

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

	// Shader Sources
	const char *vShaderStr = "/home/silviu/opengl-silviu/opengles-workspace/shaders/shader.vert";

	const char *fShaderStr = "/home/silviu/opengl-silviu/opengles-workspace/shaders/shader.frag";

	std::vector<GLfloat> vVertices_second_vector{};
	std::vector<GLfloat> vVertices_single_square_vector{
		-0.5f,0.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f,1.0f,1.0f,
		-0.5f,0.5f,0.0f,0.0f,1.0f,
	};
	std::vector<std::vector<int>> myMatrix;
	texture texture_instance;
	fps fps_instance;
	shader shader_instance;

	GLFWRenderer::GLFWRenderer(std::shared_ptr<Context> context)
		: mContext(std::move(context)),
		  shaderProgram(glCreateProgram())
	{
		vertexShader = shader_instance.LoadShader(vShaderStr, GL_VERTEX_SHADER);
		fragmentShader = shader_instance.LoadShader(fShaderStr, GL_FRAGMENT_SHADER);

		LinkProgram();
		glViewport(0, 0, 800, 800);
		
		std::string filename = "/home/silviu/opengl-silviu/opengles-workspace/src/numbers.txt";
		brick_texture_ = "/home/silviu/opengl-silviu/opengles-workspace/textures/brick.png";
		ReadNumbersFromFile(filename, rows_from_file_, columns_from_file_);
		myMatrix = initializeMatrix(rows_from_file_, columns_from_file_);
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

	void GLFWRenderer::CalculateSquareValues(std::vector<GLfloat> &vec, std::vector<GLfloat> &vec2)
	{

		GLfloat x = -1.0f;
		GLfloat y = 1.0f;
		GLfloat z = 0.0f;

		GLfloat length_value_row = 2.0f / columns_from_file_;
		GLfloat length_value_column = 2.0f / rows_from_file_;
		nr_squares_ = rows_from_file_ * columns_from_file_;
		const int nr_rows = nr_squares_ / rows_from_file_;
		const int nr_columns = nr_squares_ / columns_from_file_;

		for (int i = 1; i <= nr_columns; i++)
		{
			for (int j = 1; j <= nr_rows; j++)
			{
				GLfloat bottom_left_x = x;
				GLfloat bottom_left_y = y - length_value_column;
				GLfloat bottom_left_z = z;
				GLfloat bottom_left_u = 0.0f;
				GLfloat bottom_left_v = 0.0f;

				GLfloat bottom_right_x = x + length_value_row;
				GLfloat bottom_right_y = y - length_value_column;
				GLfloat bottom_right_z = z;
				GLfloat bottom_right_u = 1.0f;
				GLfloat bottom_right_v = 0.0f;

				GLfloat top_right_x = x + length_value_row;
				GLfloat top_right_y = y;
				GLfloat top_right_z = z;
				GLfloat top_right_u = 1.0f;
				GLfloat top_right_v = 1.0f;

				GLfloat top_left_x = x;
				GLfloat top_left_y = y;
				GLfloat top_left_z = z;
				GLfloat top_left_u = 0.0f;
				GLfloat top_left_v = 1.0f;

				if ((i % 2 != 0 && j % 2 != 0) || (i % 2 == 0 && j % 2 == 0))
				{
					vec.push_back(bottom_left_x);
					vec.push_back(bottom_left_y);
					vec.push_back(bottom_left_z);
					vec.push_back(bottom_left_u);
					vec.push_back(bottom_left_v);
					vec.push_back(bottom_right_x);
					vec.push_back(bottom_right_y);
					vec.push_back(bottom_right_z);
					vec.push_back(bottom_right_u);
					vec.push_back(bottom_right_v);
					vec.push_back(top_right_x);
					vec.push_back(top_right_y);
					vec.push_back(top_right_z);
					vec.push_back(top_right_u);
					vec.push_back(top_right_v);
					vec.push_back(top_left_x);
					vec.push_back(top_left_y);
					vec.push_back(top_left_z);
					vec.push_back(top_left_u);
					vec.push_back(top_left_v);
				}
				else
				{
					vec2.push_back(bottom_left_x);
					vec2.push_back(bottom_left_y);
					vec2.push_back(bottom_left_z);
					vec2.push_back(bottom_left_u);
					vec2.push_back(bottom_left_v);
					vec2.push_back(bottom_right_x);
					vec2.push_back(bottom_right_y);
					vec2.push_back(bottom_right_z);
					vec2.push_back(bottom_right_u);
					vec2.push_back(bottom_right_v);
					vec2.push_back(top_right_x);
					vec2.push_back(top_right_y);
					vec2.push_back(top_right_z);
					vec2.push_back(top_right_u);
					vec2.push_back(top_right_v);
					vec2.push_back(top_left_x);
					vec2.push_back(top_left_y);
					vec2.push_back(top_left_z);
					vec2.push_back(top_left_u);
					vec2.push_back(top_left_v);
				}

				x = x + length_value_row;
			}

			x = -1.0f;
			y = y - length_value_column;
		}
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

	bool GLFWRenderer::ReadNumbersFromFile(const std::string &filename, int &num1, int &num2)
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


	std::vector<std::vector<int>> GLFWRenderer::initializeMatrix(int rows, int columns)
	{
		std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns, 0)); // Initialize matrix with zeros

		// Set value at [1][1] index to 1 (assuming 0-based indexing)
		if (rows > 1 && columns > 1)
		{
			matrix[1][1] = 1;
		}
		else
		{
			std::cout << "Matrix dimensions should be greater than 1x1.\n";
		}

		return matrix;
	}

	void GLFWRenderer::MoveOneDown(std::vector<std::vector<int>> &matrix)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (matrix[i][j] == 1)
				{
					if (i >= 0)
					{ // Move up a row if possible
						matrix[i][j] = 0;
						matrix[i + 1][j] = 1;
						return;
					}
				}
			}
		}
	}

	void GLFWRenderer::MoveOneUp(std::vector<std::vector<int>> &matrix)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (matrix[i][j] == 1)
				{
					if (i > 0)
					{ // Move up a row if possible
						matrix[i][j] = 0;
						matrix[i - 1][j] = 1;
						return;
					}
				}
			}
		}
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

	bool GLFWRenderer::CheckLastRowForOne(const std::vector<std::vector<int>> &matrix)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();

		for (int j = 0; j < cols; ++j)
		{
			if (matrix[rows - 1][j] == 1)
			{
				return true; // If 1 is found in the last row, return true
			}
		}

		return false; // If 1 is not found in the last row, return false
	}

	bool GLFWRenderer::CheckFirstRowForOne(const std::vector<std::vector<int>> &matrix)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();

		for (int j = 0; j < cols; ++j)
		{
			if (matrix[0][j] == 1)
			{
				return true; // If 1 is found in the last row, return true
			}
		}

		return false; // If 1 is not found in the last row, return false
	}
	
	bool GLFWRenderer::poll()
	{
		long long current_time = fps_instance.GetCurrentTimeMillis();
		float elapsed_time = (current_time - fps_instance.GetStartTime()) / 1000.0f;
		int target_fps = 1;

		if (elapsed_time >= 1.0f / target_fps)
		{

			render();

			if (CheckLastRowForOne(myMatrix))
			{
				lower_limit_reached_ = true;
			}
			else if (CheckFirstRowForOne(myMatrix))
			{
				lower_limit_reached_ = false;
			}

			if (lower_limit_reached_)
			{
				IncrementYCoordinate(vVertices_single_square_vector, 0.5f); // patratu x y
				MoveOneUp(myMatrix); // 
				//std::cout<<"if" << std::endl;
				//printMatrix(myMatrix);
			}
			else
			{
				DecrementYCoordinate(vVertices_single_square_vector, 0.5f);
				MoveOneDown(myMatrix);
				//std::cout<<"else" << std::endl;
				//printMatrix(myMatrix);
			}

			fps_instance.SetStartTime(current_time);
		}

		return true;
	}

} // namespace opengles_workspace