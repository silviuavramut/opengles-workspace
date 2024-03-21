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
        void CalculateSquareValues(std::vector<GLfloat> &vec, std::vector<GLfloat> &vec2);
        bool ReadNumbersFromFile(const std::string &filename, int &num1, int &num2);

        int rows_from_file_;
		int columns_from_file_;

        ~helper();


    private:

		GLfloat x_ = -1.0f;
		GLfloat y_ = 1.0f;
		GLfloat z_ = 0.0f;


		GLfloat length_value_row = 2.0f / columns_from_file_;
		GLfloat length_value_column = 2.0f / rows_from_file_;

    };
}