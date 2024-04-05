#pragma once

#include <vector>
#include <glad/gl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


namespace opengles_workspace
{
    class helper
    {
    public:
        helper();

        bool ReadNumbersFromFile(const std::string &filename, int &num1, int &num2);
        std::vector<GLfloat> CalculateSquareVertices(const std::vector<std::vector<int>> &matrix,  float cellWidth, float cellHeight);


        ~helper();


    private:

		GLfloat x_ = -1.0f;
		GLfloat y_ = 1.0f;
		GLfloat z_ = 0.0f;


    };
}