#pragma once
#include <chrono>
#include <context.hpp>
#include <memory>
#include <optional>
#include <polled_object.hpp>
#include <vector>

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
		//OpenGL functions 
		void CompileShaders();
		void LinkProgram();

		//Functions that work with coordinates
		void CalculateSquareValues(std::vector<GLfloat> &vec,std::vector<GLfloat> &vec2);

		//Rendering functions
		void ClearBackBuffer();
		void DrawWithTexture(std::vector<GLfloat> &vertices, char *textureFileLoc);
		void IncrementYCoordinate(std::vector<GLfloat> &vertices, float offset);
		void DecrementYCoordinate(std::vector<GLfloat> &vertices, float offset);

		//Helper functions		
		bool CheckProgramStatus(GLuint programId);
		bool CheckUniformLocationError(GLint location, const char *variableName);
		bool ReadNumbersFromFile(const std::string &filename, int &num1, int &num2);
		long long GetCurrentTimeMillis();

		GLuint vertexShader, fragmentShader, shaderProgram;
		GLuint VAO, VBO;

		const size_t kVerticesPerSquare = 4;
		long long start_time_;
		size_t nr_squares_;
		int rows_from_file_;
		int columns_from_file_;
		char *brick_texture_;

		std::shared_ptr<Context> mContext;
		GLFWwindow *window() const
		{
			return static_cast<GLFWwindow *>(mContext->window());
		}
	};
} // namespace opengles_workspace