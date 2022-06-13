#pragma once
#include "MazeSolverNative.h"
#include <vector>
#include <tuple>

struct MatrixValue
{
    int m_Row = -1, m_Col = -1;
};


MAZESOLVERNATIVE_API void createGraphNative(const char* filename);
MAZESOLVERNATIVE_API void getGraphMatrixNative(int& rows, int& cols, std::vector<std::vector<int>>& mazeMatrix);
MAZESOLVERNATIVE_API std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool>* findPathUsingDFSNative(int &row, int &col);
MAZESOLVERNATIVE_API std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool>* findPathUsingNonGreedyASTARNative(int& st_row, int& st_col, int& end_row, int end_col);



