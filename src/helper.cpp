#include <helper.hpp>

namespace opengles_workspace
{
    helper::helper()
    {
    }

    // 	void helper::CalculateSquareValues(std::vector<GLfloat> &vec, std::vector<GLfloat> &vec2)
    // {

    // 	nr_squares_ = rows_from_file_ * columns_from_file_;
    // 	const int nr_rows = nr_squares_ / rows_from_file_;
    // 	const int nr_columns = nr_squares_ / columns_from_file_;

    // 	for (int i = 1; i <= nr_columns; i++)
    // 	{
    // 		for (int j = 1; j <= nr_rows; j++)
    // 		{
    // 			GLfloat bottom_left_x = x;
    // 			GLfloat bottom_left_y = y - length_value_column;
    // 			GLfloat bottom_left_z = z;
    // 			GLfloat bottom_left_u = 0.0f;
    // 			GLfloat bottom_left_v = 0.0f;

    // 			GLfloat bottom_right_x = x + length_value_row;
    // 			GLfloat bottom_right_y = y - length_value_column;
    // 			GLfloat bottom_right_z = z;
    // 			GLfloat bottom_right_u = 1.0f;
    // 			GLfloat bottom_right_v = 0.0f;

    // 			GLfloat top_right_x = x + length_value_row;
    // 			GLfloat top_right_y = y;
    // 			GLfloat top_right_z = z;
    // 			GLfloat top_right_u = 1.0f;
    // 			GLfloat top_right_v = 1.0f;

    // 			GLfloat top_left_x = x;
    // 			GLfloat top_left_y = y;
    // 			GLfloat top_left_z = z;
    // 			GLfloat top_left_u = 0.0f;
    // 			GLfloat top_left_v = 1.0f;

    // 			if ((i % 2 != 0 && j % 2 != 0) || (i % 2 == 0 && j % 2 == 0))
    // 			{
    // 				vec.push_back(bottom_left_x);
    // 				vec.push_back(bottom_left_y);
    // 				vec.push_back(bottom_left_z);
    // 				vec.push_back(bottom_left_u);
    // 				vec.push_back(bottom_left_v);
    // 				vec.push_back(bottom_right_x);
    // 				vec.push_back(bottom_right_y);
    // 				vec.push_back(bottom_right_z);
    // 				vec.push_back(bottom_right_u);
    // 				vec.push_back(bottom_right_v);
    // 				vec.push_back(top_right_x);
    // 				vec.push_back(top_right_y);
    // 				vec.push_back(top_right_z);
    // 				vec.push_back(top_right_u);
    // 				vec.push_back(top_right_v);
    // 				vec.push_back(top_left_x);
    // 				vec.push_back(top_left_y);
    // 				vec.push_back(top_left_z);
    // 				vec.push_back(top_left_u);
    // 				vec.push_back(top_left_v);
    // 			}
    // 			else
    // 			{
    // 				vec2.push_back(bottom_left_x);
    // 				vec2.push_back(bottom_left_y);
    // 				vec2.push_back(bottom_left_z);
    // 				vec2.push_back(bottom_left_u);
    // 				vec2.push_back(bottom_left_v);
    // 				vec2.push_back(bottom_right_x);
    // 				vec2.push_back(bottom_right_y);
    // 				vec2.push_back(bottom_right_z);
    // 				vec2.push_back(bottom_right_u);
    // 				vec2.push_back(bottom_right_v);
    // 				vec2.push_back(top_right_x);
    // 				vec2.push_back(top_right_y);
    // 				vec2.push_back(top_right_z);
    // 				vec2.push_back(top_right_u);
    // 				vec2.push_back(top_right_v);
    // 				vec2.push_back(top_left_x);
    // 				vec2.push_back(top_left_y);
    // 				vec2.push_back(top_left_z);
    // 				vec2.push_back(top_left_u);
    // 				vec2.push_back(top_left_v);
    // 			}

    // 			x = x + length_value_row;
    // 		}

    // 		x = -1.0f;
    // 		y = y - length_value_column;
    // 	}
    // }

    bool helper::ReadNumbersFromFile(const std::string &filename, int &num1, int &num2)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return false;
        }

        std::string line;
        if (std::getline(file, line))
        {
            std::istringstream iss(line);
            char comma;
            if (iss >> num1 >> comma >> num2)
            {
                if (comma != ',')
                {
                    std::cerr << "Error: Expected comma delimiter" << std::endl;
                    return false;
                }
                return true;
            }
            else
            {
                std::cerr << "Error: Unable to read numbers from line" << std::endl;
                return false;
            }
        }
        else
        {
            std::cerr << "Error: File is empty" << std::endl;
            return false;
        }
    }

    helper::~helper()
    {
    }
}