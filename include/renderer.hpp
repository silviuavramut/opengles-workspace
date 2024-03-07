#pragma once
#include <memory>
#include <optional>
#include <context.hpp>
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
		void calculate_square_values(std::vector<GLfloat> &vec, std::vector<GLfloat> &vec2);
		void draw(GLuint shader_program, std::vector<GLfloat> &vertices, std::vector<GLfloat> color);
		void clear_back_buffer();
		bool checkProgramStatus(GLuint programId);
		bool checkUniformLocationError(GLint location, const char* variableName);
		std::shared_ptr<Context> mContext;
		GLFWwindow *window() const { return static_cast<GLFWwindow *>(mContext->window()); }
	};
}