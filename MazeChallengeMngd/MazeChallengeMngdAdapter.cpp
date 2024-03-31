
#include "MazeChallengeMngdAdapter.h"
#include <MazeSolverNative/MazeSolverAdapterNative.h>
#include <msclr\marshal_cppstd.h>

void MazeChallengeAdapterNS::MazeSolverMngdAdapter::CreateGraph(System::String^ mngdFilename)
{
    std::string nativeFilename = msclr::interop::marshal_as<std::string>(mngdFilename);
    createGraphNative(nativeFilename.c_str());
    
    std::vector<std::vector<int>> nativeMazeMatrix;
    int rows = 0, cols = 0;
    getGraphMatrixNative(rows, cols, nativeMazeMatrix);
    this->m_Rows = rows;
    this->m_Cols = cols;

    if (this->m_Rows != 0 && this->m_Cols != 0)
        m_MazeMatrix = gcnew List<List<int>^>();
    for (int ii = 0; ii < rows; ii++)
    {
        List<int>^ listOfListItem = gcnew List<int>();
        m_MazeMatrix->Add(listOfListItem);
    }
    for (int ii = 0; ii < rows; ii++)
    {
        for (int jj = 0; jj < cols; jj++)
        {
            m_MazeMatrix[ii]->Add(nativeMazeMatrix[jj][ii]);
        }

        int aa = 0;
        ++aa;
    }
}

List<List<MazeChallengeAdapterNS::Cell^>^>^ MazeChallengeAdapterNS::MazeSolverMngdAdapter::FindPathUsingDFS(int row, int col)
{
    List<List<MazeChallengeAdapterNS::Cell^>^>^ allSolutionPathsMngd;
    std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool> *allSolutionPathsResult = findPathUsingDFSNative(row, col);
    auto allSolutionPathsNative = std::get<0>(*allSolutionPathsResult);
    m_ContainsCycles = std::get<1>(*allSolutionPathsResult);
    allSolutionPathsMngd = gcnew List<List<MazeChallengeAdapterNS::Cell^>^>();

    for (int ii = 0; ii < allSolutionPathsNative.size(); ii++)
    {
        List<MazeChallengeAdapterNS::Cell^> ^pathMngd = gcnew List<MazeChallengeAdapterNS::Cell^>();
        for (int jj = 0; jj < allSolutionPathsNative[ii].size(); jj++)
        {
            int rowN = std::get<0>(allSolutionPathsNative[ii][jj]);
            int colN = std::get<1>(allSolutionPathsNative[ii][jj]);

            MazeChallengeAdapterNS::Cell^ newCell = gcnew MazeChallengeAdapterNS::Cell(rowN, colN);
            pathMngd->Add(newCell);
        }
        allSolutionPathsMngd->Add(pathMngd);
    }
    return allSolutionPathsMngd;
}

List<List<MazeChallengeAdapterNS::Cell^>^>^ MazeChallengeAdapterNS::MazeSolverMngdAdapter::FindPathUsingNonGreedyASTAR(int st_row, int st_col, int end_row, int end_col)
{
    List<List<MazeChallengeAdapterNS::Cell^>^>^ allSolutionPathsMngd;
    std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool>* allSolutionPathsResult = findPathUsingNonGreedyASTARNative(st_row, st_col, end_row, end_col);
    auto allSolutionPathsNative = std::get<0>(*allSolutionPathsResult);
    m_ContainsCycles = std::get<1>(*allSolutionPathsResult);

    allSolutionPathsMngd = gcnew List<List<MazeChallengeAdapterNS::Cell^>^>();
    for (int ii = 0; ii < allSolutionPathsNative.size(); ii++)
    {
        List<MazeChallengeAdapterNS::Cell^>^ pathMngd = gcnew List<MazeChallengeAdapterNS::Cell^>();
        for (int jj = 0; jj < allSolutionPathsNative[ii].size(); jj++)
        {
            int rowN = std::get<0>(allSolutionPathsNative[ii][jj]);
            int colN = std::get<1>(allSolutionPathsNative[ii][jj]);

            MazeChallengeAdapterNS::Cell^ newCell = gcnew MazeChallengeAdapterNS::Cell(rowN, colN);
            pathMngd->Add(newCell);
        }
        allSolutionPathsMngd->Add(pathMngd);
    }
    return allSolutionPathsMngd;
}
