#pragma once

#include <vector>
#include <glad/gl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


namespace opengles_workspace
{
    class game
    {
    public:
        game();
        std::vector<std::vector<int>> initializeMatrix(int rows, int columns);
        void MoveOneDown(std::vector<std::vector<int>> &matrix);
        void MoveOneUp(std::vector<std::vector<int>> &matrix);
        bool CheckLastRowForOne(const std::vector<std::vector<int>> &matrix);
        bool CheckFirstRowForOne(const std::vector<std::vector<int>> &matrix);

        ~game();


    private:

    };
}