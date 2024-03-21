#include <game.hpp>

namespace opengles_workspace
{

    game::game()
    {
    }

    std::vector<std::vector<int>> game::initializeMatrix(int rows, int columns)
    {
        std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns, 0)); // Initialize matrix with zeros

        // Set value at [1][1] index to 1 (assuming 0-based indexing)
        if (rows > 1 && columns > 1)
        {
            matrix[1][1] = 1;
        }
        else
        {
            std::cout << "Matrix dimensions should be greater than 1x1.\n";
        }

        return matrix;
    }

    void game::MoveOneDown(std::vector<std::vector<int>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == 1)
                {
                    if (i >= 0)
                    { // Move up a row if possible
                        matrix[i][j] = 0;
                        matrix[i + 1][j] = 1;
                        return;
                    }
                }
            }
        }
    }
    void game::MoveOneUp(std::vector<std::vector<int>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == 1)
                {
                    if (i > 0)
                    { // Move up a row if possible
                        matrix[i][j] = 0;
                        matrix[i - 1][j] = 1;
                        return;
                    }
                }
            }
        }
    }

    bool game::CheckLastRowForOne(const std::vector<std::vector<int>> &matrix)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();

		for (int j = 0; j < cols; ++j)
		{
			if (matrix[rows - 1][j] == 1)
			{
				return true; // If 1 is found in the last row, return true
			}
		}

		return false; // If 1 is not found in the last row, return false
	}

	bool game::CheckFirstRowForOne(const std::vector<std::vector<int>> &matrix)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();

		for (int j = 0; j < cols; ++j)
		{
			if (matrix[0][j] == 1)
			{
				return true; // If 1 is found in the last row, return true
			}
		}

		return false; // If 1 is not found in the last row, return false
	}

    game::~game()
    {
    }

}