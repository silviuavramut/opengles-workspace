#include <shader.hpp>

namespace opengles_workspace
{
    shader::shader()
    {
    }

    GLuint shader::LoadShader(const char *filename, GLenum shaderType)
    {
        // Open the shader file
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return 0;
        }

        // Read the shader code into a string
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string shaderCode = buffer.str();
        const char *shaderSource = shaderCode.c_str();

        // Create shader object
        GLuint shader = glCreateShader(shaderType);

        // Load shader source
        glShaderSource(shader, 1, &shaderSource, NULL);

        // Compile shader
        glCompileShader(shader);

        // Check for compilation errors
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> log(logLength);
            glGetShaderInfoLog(shader, logLength, NULL, log.data());
            std::cerr << "Shader compilation error in " << filename << ":\n"
                      << log.data() << std::endl;
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    shader::~shader()
    {
    }
}