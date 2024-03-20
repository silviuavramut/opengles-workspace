#pragma once

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

		//Game functions
		std::vector<std::vector<int>> initializeMatrix(int rows, int columns);
		void MoveOneDown(std::vector<std::vector<int>> &matrix);
		void MoveOneUp(std::vector<std::vector<int>> &matrix);
		bool CheckLastRowForOne(const std::vector<std::vector<int>> &matrix);
		bool CheckFirstRowForOne(const std::vector<std::vector<int>> &matrix);

		GLuint vertexShader, fragmentShader, shaderProgram;
		GLuint VAO, VBO;

		const size_t kVerticesPerSquare = 4;
	
		size_t nr_squares_;
		int rows_from_file_;
		int columns_from_file_;
		char *brick_texture_;
		bool lower_limit_reached_;

		std::shared_ptr<Context> mContext;
		GLFWwindow *window() const
		{
			return static_cast<GLFWwindow *>(mContext->window());
		}
	};
} // namespace opengles_workspace