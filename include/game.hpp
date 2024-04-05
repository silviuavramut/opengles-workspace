#pragma once

#include <vector>
#include <glad/gl.h>
#include <polled_object.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


namespace opengles_workspace
{
    class game : public PolledObject
    {
    public:
        game();
        std::vector<std::vector<int>> initializeMatrix(int rows, int columns);
        void MoveOneDown(std::vector<std::vector<int>> &matrix);
        void MoveOneLeft(std::vector<std::vector<int>> &matrix);
        void MoveOneRight(std::vector<std::vector<int>> &matrix);
        bool CheckLastRowForOne(const std::vector<std::vector<int>> &matrix);
        bool HitsLowerBoundary(std::vector<std::vector<int>>& matrix);
        void TransformBoundary(std::vector<std::vector<int>> &matrix);
        bool HitsLeftBoundary(const std::vector<std::vector<int>>& matrix);
        bool HitsRightBoundary(const std::vector<std::vector<int>>& matrix);
        void AddNewTwo(std::vector<std::vector<int>> &matrix);

        bool poll() override;

        ~game();


    private:

    	std::vector<std::vector<int>> game_matrix;
        bool is_on_last_row;

    };
}