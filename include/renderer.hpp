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

		void render();

		bool poll() override;

	private:
		// OpenGL functions
		void LinkProgram();

		// Rendering functions
		void ClearBackBuffer();
		void DrawWithTexture(std::vector<GLfloat> &vertices, char *textureFileLoc);
		void IncrementYCoordinate(std::vector<GLfloat> &vertices, float offset);
		void DecrementYCoordinate(std::vector<GLfloat> &vertices, float offset);

		// Helper functions
		bool CheckProgramStatus(GLuint programId);
		bool CheckUniformLocationError(GLint location, const char *variableName);



		GLuint vertexShader, fragmentShader, shaderProgram;
		GLuint VAO, VBO;

		std::vector<GLfloat> vVertices_single_square_vector{
			-0.5f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f,0.0f,
			0.0f,0.5f,0.0f,1.0f,1.0f,
			-0.5f,0.5f,0.0f,0.0f,1.0f,
		};

		const size_t kVerticesPerSquare = 4;

		size_t nr_squares_;
		int rows_from_file_;
		int columns_from_file_;
		bool lower_limit_reached_;

		// Shader Sources
		const char *vShaderStr = "/home/silviu/opengl-silviu/opengles-workspace/shaders/shader.vert";
		const char *fShaderStr = "/home/silviu/opengl-silviu/opengles-workspace/shaders/shader.frag";

		std::string filename = "/home/silviu/opengl-silviu/opengles-workspace/src/numbers.txt";
		char *brick_texture_ = "/home/silviu/opengl-silviu/opengles-workspace/textures/brick.png";

		std::shared_ptr<Context> mContext;
		GLFWwindow *window() const
		{
			return static_cast<GLFWwindow *>(mContext->window());
		}
	};
} // namespace opengles_workspace