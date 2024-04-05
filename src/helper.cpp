#include <helper.hpp>

namespace opengles_workspace
{
    helper::helper()
    {
    }

    std::vector<GLfloat> helper::CalculateSquareVertices(const std::vector<std::vector<int>> &matrix, float cellWidth, float cellHeight)
    {
        std::vector<GLfloat> vertices;

        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                if (matrix[i][j] != 0)
                {
                    // Map the matrix indices to OpenGL coordinates
                    float x = -1.0f + (float)j * cellWidth;
                    float y = 1.0f - (float)i * cellHeight;


                    vertices.push_back(x);
                    vertices.push_back(y - cellHeight);
                    vertices.push_back(0.0f); 
                    vertices.push_back(0.0f); 
                    vertices.push_back(1.0f); 

                    vertices.push_back(x + cellWidth);
                    vertices.push_back(y - cellHeight);
                    vertices.push_back(0.0f); 
                    vertices.push_back(1.0f); 
                    vertices.push_back(1.0f); 

                    vertices.push_back(x + cellWidth);
                    vertices.push_back(y);
                    vertices.push_back(0.0f); 
                    vertices.push_back(1.0f); 
                    vertices.push_back(0.0f); 

                    vertices.push_back(x);
                    vertices.push_back(y);
                    vertices.push_back(0.0f); 
                    vertices.push_back(0.0f); 
                    vertices.push_back(0.0f); 
                }
            }
        }

        return vertices;
    }

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