#include <game.hpp>

namespace opengles_workspace
{

    game::game()
    {
    }

    std::vector<std::vector<int>> game::initializeMatrix(int rows, int columns)
    {
        std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns, 0)); // Initialize matrix with 0s

        // Set [0,0] index to 2
        matrix[0][4] = 2;

        // Fill the last row with 1 values
        for (int j = 0; j < columns; ++j)
        {
            matrix[rows - 1][j] = 1;
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
                if (matrix[i][j] == 2)
                {
                    if (i >= 0)
                    { // Move up a row if possible
                        matrix[i][j] = 0;
                        matrix[i + 1][j] = 2;
                        return;
                    }
                }
            }
        }
    }
    void game::MoveOneLeft(std::vector<std::vector<int>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == 2)
                {
                    if (i >= 0)
                    { // Move left a row if possible
                        matrix[i][j] = 0;
                        matrix[i][j - 1] = 2;
                        return;
                    }
                }
            }
        }
    }
    void game::MoveOneRight(std::vector<std::vector<int>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (matrix[i][j] == 2)
                {
                    if (i >= 0)
                    { // Move right a row if possible
                        matrix[i][j] = 0;
                        matrix[i][j + 1] = 2;
                        return;
                    }
                }
            }
        }
    }

    bool game::HitsLowerBoundary(std::vector<std::vector<int>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        // Iterate through the matrix
        for (int i = 0; i < rows - 1; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                // Check if the current element is '2'
                if (matrix[i][j] == 2)
                {
                    // Check if the row below exists and if it contains any '1'
                    if (matrix[i + 1][j] == 1)
                        return true; // '2' hits the boundary
                }
            }
        }

        return false; // '2' does not hit the boundary
    }
    void game::TransformBoundary(std::vector<std::vector<int>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        // Iterate through the matrix
        for (int i = 0; i < rows - 1; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                // Check if the current element is '2'
                if (matrix[i][j] == 2)
                {
                    // Check if the row below exists and if it contains any '1'
                    if (matrix[i + 1][j] == 1)
                    {
                        // Transform '2' into '1'
                        matrix[i][j] = 1;
                        return;
                    }
                }
            }
        }
    }

    bool game::HitsLeftBoundary(const std::vector<std::vector<int>> &matrix)
    {
        for (const auto &row : matrix)
        {
            if (row.front() == 2)
                return true;
        }
        return false;
    }

    bool game::HitsRightBoundary(const std::vector<std::vector<int>> &matrix)
    {
        for (const auto &row : matrix)
        {
            if (row.back() == 2)
                return true;
        }
        return false;
    }

    void game::AddNewTwo(std::vector<std::vector<int>> &matrix)
    {
        // Add '2' at the (0,0) index of the matrix
        matrix[0][4] = 2;
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

    bool game::poll()
    {

        return true;
    }

    game::~game()
    {
    }

}