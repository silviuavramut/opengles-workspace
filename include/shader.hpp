#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>

#include <glad/gl.h>

namespace opengles_workspace
{
    class shader
    {
    public:
        shader();
        GLuint LoadShader(const char *filename, GLenum shaderType);
        void LinkProgram();
        

        ~shader();

    private:
    };
}