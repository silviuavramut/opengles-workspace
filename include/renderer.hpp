#pragma once

#include <context.hpp>
#include <memory>
#include <optional>
#include <polled_object.hpp>
#include <vector>
#include <iostream>

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace opengles_workspace
{
	class GLFWRenderer : public PolledObject
	{
	public:
		GLFWRenderer(std::shared_ptr<Context> context);

		~GLFWRenderer() = default;
		void DrawWithTexture(std::vector<GLfloat> &vertices, char *textureFileLoc);

		void AppendVertices(std::vector<GLfloat> &vertices, const std::vector<GLfloat> &newVertices);
		
		void render();

		bool poll() override;

		std::vector<GLfloat> square_vertices_vector;
		char *brick_texture_ = "/home/silviu/opengl-silviu/opengles-workspace/textures/brick.png";
		std::vector<std::vector<int>> game_matrix;

		GLfloat horizontal_offset_;
		GLfloat vertical_offset_;
		GLfloat cell_width;
		GLfloat cell_height;


	private:
		// OpenGL functions
		void LinkProgram();

		// Rendering functions
		void ClearBackBuffer();

		// Helper functions
		bool CheckProgramStatus(GLuint programId);
		bool CheckUniformLocationError(GLint location, const char *variableName);

		GLuint vertexShader, fragmentShader, shaderProgram;
		GLuint VAO, VBO;

		const size_t kVerticesPerSquare = 4;

		size_t nr_squares_;
		int rows_from_file_;
		int columns_from_file_;


		// Shader Sources
		const char *vShaderStr = "/home/silviu/opengl-silviu/opengles-workspace/shaders/shader.vert";
		const char *fShaderStr = "/home/silviu/opengl-silviu/opengles-workspace/shaders/shader.frag";

		std::string filename = "/home/silviu/opengl-silviu/opengles-workspace/src/numbers.txt";

		std::shared_ptr<Context> mContext;
		GLFWwindow *window() const
		{
			return static_cast<GLFWwindow *>(mContext->window());
		}
	};
} // namespace opengles_workspace