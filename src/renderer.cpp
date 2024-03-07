#include <renderer.hpp>
#include <exception.hpp>

#include <memory>
#include <optional>
#include <cassert>
#include <array>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// #include <esUtil.h>

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
		"uniform vec4 u_color;                        \n"
		"out vec4 FragColor;                          \n"
		"void main()                                  \n"
		"{                                            \n"
		"   FragColor = u_color;  \n"
		"}                                            \n";

	std::vector<GLfloat> vVertices_white{};
	std::vector<GLfloat> vVertices_blue{};
	GLuint vertexShader,fragmentShader,shaderProgram;

	GLFWRenderer::GLFWRenderer(std::shared_ptr<Context> context)
		: mContext(std::move(context))
	{
		// Initialize the shaders and the program
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		GLuint shaderProgram = glCreateProgram();

		glShaderSource(vertexShader, 1, &vShaderStr, nullptr);
		glCompileShader(vertexShader);

		glShaderSource(fragmentShader, 1, &fShaderStr, nullptr);
		glCompileShader(fragmentShader);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void GLFWRenderer::render()
	{

		std::vector<GLfloat> white_color = {0.0f, 0.0f, 1.0f, 1.0f};
		std::vector<GLfloat> blue_color = {0.0f, 0.0f, 1.0f, 1.0f};
		clear_back_buffer();
		calculate_square_values(vVertices_white, vVertices_blue);
		draw(shaderProgram, vVertices_white, white_color);
		//draw(shaderProgram, vVertices_blue);

		glfwSwapBuffers(window());
	}
	void GLFWRenderer::clear_back_buffer(){
			// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLFWRenderer::calculate_square_values(std::vector<GLfloat> &vec, std::vector<GLfloat> &vec2)
	{

		const size_t nr_squares = 64;
		const size_t vertices_per_square = 4;
		GLfloat x = -1.0f;
		GLfloat y = 1.0f;
		GLfloat z = 0.0f;
		GLfloat length_value = 0.25f;
		const int nr_rows = nr_squares / 8;
		const int nr_columns = nr_squares / 8;

		for (int i = 1; i <= nr_columns; i++)
		{
			for (int j = 1; j <= nr_rows; j++)
			{
				GLfloat bottom_left_x = x;
				GLfloat bottom_left_y = y - length_value;
				GLfloat bottom_left_z = z;

				GLfloat bottom_right_x = x + length_value;
				GLfloat bottom_right_y = y - length_value;
				GLfloat bottom_right_z = z;

				GLfloat top_right_x = x + length_value;
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

				x = x + length_value;
			}

			x = -1.0f;
			y = y - length_value;
		}
	}

	void GLFWRenderer::draw(GLuint shaderProgram,std::vector<GLfloat> &vertices, std::vector<GLfloat> color)
	{

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
		// Bind the VAO so OpenGL knows to use it

		GLint colorLoc = glGetUniformLocation(shaderProgram, "u_color");
		glUniform4f(colorLoc, color[0], color[1], color[2], color[3]);

		glBindVertexArray(VAO);
		glDrawArrays(GL_QUADS, 0, 4 * 32);

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