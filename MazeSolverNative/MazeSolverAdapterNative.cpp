#include "MazeSolverAdapterNative.h"

#include "Node.h"
#include "Graph.h"
#include "CommandsManager.h"
#include "InputOutput.h"
#include "Init.h"

GraphCreationCommandOutput outputFromCreateGraphCmd;
MAZESOLVERNATIVE_API void createGraphNative(const char* filename)
{
    Init();


    // Maze to Graph creation command execution
    
    {
        // First command to create the Graph from maze matrix. The graph is a singleton object.
        GraphCreationCommandInput graphCreationInputdata{ filename };
        auto creationCommand = CommandsManager::GetInstance()->GetCommand("GraphCreationCommand");
        creationCommand->SetData(std::any(graphCreationInputdata));

        // Execute the command GraphCreationCommand
        creationCommand->Execute();

        // Get the data from the GraphCreationCommand command
        GraphCreationCommandOutput output;
        output.m_Graph = nullptr;
        auto anyOutputFromCreateGraphCmd = std::any(output);
        creationCommand->GetData(anyOutputFromCreateGraphCmd);
        outputFromCreateGraphCmd = std::any_cast<GraphCreationCommandOutput>(anyOutputFromCreateGraphCmd);
    }
}

MAZESOLVERNATIVE_API void getGraphMatrixNative(int& rows, int& cols, std::vector<std::vector<int>>& mazeMatrix)
{
    GraphCreationCommandOutput outputFromCreateGraphCmd;

    auto creationCommand = CommandsManager::GetInstance()->GetCommand("GraphCreationCommand");

    outputFromCreateGraphCmd.m_Graph = nullptr;
    auto anyOutputFromCreateGraphCmd = std::any(outputFromCreateGraphCmd);
    creationCommand->GetData(anyOutputFromCreateGraphCmd);
    outputFromCreateGraphCmd = std::any_cast<GraphCreationCommandOutput>(anyOutputFromCreateGraphCmd);

    rows = outputFromCreateGraphCmd.m_Graph->GetTotalRows();
    cols = outputFromCreateGraphCmd.m_Graph->GetTotalColumns();
    mazeMatrix = outputFromCreateGraphCmd.m_Graph->getMazeMatrix();
}


MAZESOLVERNATIVE_API std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool>* findPathUsingDFSNative(int &row, int &col)
{
    std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool>* result = nullptr;
    std::vector<std::vector<std::tuple<int, int>>> allSolutionPaths;
    GraphPathFinderOutput pathFinderCmdOutputDFSStrategy;
    {

        GraphPathFinderInput graphPathFinderInput;

        // To give two different inputs for the maze_02_2_connected_components.txt, 
        // use outputFromCreateGraphCmd.m_EndNodes[0] OR outputFromCreateGraphCmd.m_EndNodes[1] below.
        // This chooses 0,2 or 0,5
        graphPathFinderInput.m_StartNode = outputFromCreateGraphCmd.m_Graph->getGraphNode(row, col);
        graphPathFinderInput.m_Strategy = PathFindingSTrategy::DFS;

        auto graphPathFinderCommandDFSStrategy = CommandsManager::GetInstance()->GetCommand("GraphPathFinderCommand");
        graphPathFinderCommandDFSStrategy->SetData(std::any(graphPathFinderInput));

        // Set Input to the command GraphPathFinderCommand with NonGreedyASTAR strategy
        graphPathFinderCommandDFSStrategy->Execute();

        // Fetch the output from the command GraphPathFinderCommand with NonGreedyASTAR strategy
        auto anyPathFinderCmdOutputDFSStrategy = std::any(pathFinderCmdOutputDFSStrategy);
        graphPathFinderCommandDFSStrategy->GetData(anyPathFinderCmdOutputDFSStrategy);
        pathFinderCmdOutputDFSStrategy = std::any_cast<GraphPathFinderOutput>(anyPathFinderCmdOutputDFSStrategy);

        // Print the DFS paths
        std::cout << "\n All Possible Paths in DFS strategy are" << std::endl;
        outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdOutputDFSStrategy.m_AllPaths);

        std::cout << "\n Feasible solution Paths in DFS strategy are" << std::endl;
        outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths);

        bool containsCycles = false;
        if (pathFinderCmdOutputDFSStrategy.m_containsCycles)
        {
            std::cout << "\n **The Graph contains one or more cycles **" << std::endl;
            containsCycles = true;
        }
        
        for (int ii = 0; ii < pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths.size(); ii++)
        {
            std::vector<std::tuple<int, int>> solutionPath;
            for (int jj = 0; jj < pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths[ii].size(); jj++)
            {
                auto graphPathCoord = pathFinderCmdOutputDFSStrategy.m_AllSolutionPaths[ii][jj];
                auto coord = std::make_tuple<int, int>(graphPathCoord->getRow(), graphPathCoord->getCol());
                solutionPath.push_back(coord);
            }
            allSolutionPaths.push_back(solutionPath);
        }

        result = new std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool >(allSolutionPaths, containsCycles);
        return result;
    }
}

MAZESOLVERNATIVE_API std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool>* findPathUsingNonGreedyASTARNative(int& st_row, int& st_col, int &end_row, int end_col)
{
    std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool>* result = nullptr;
    std::vector<std::vector<std::tuple<int, int>>> allSolutionPaths;

    GraphPathFinderInput graphPathFinderASTARStrategyInput;
    GraphPathFinderOutput pathFinderCmdNonGreedyASTAROutput;

    graphPathFinderASTARStrategyInput.m_StartNode = outputFromCreateGraphCmd.m_Graph->getGraphNode(st_row, st_col);
    graphPathFinderASTARStrategyInput.m_EndNode = outputFromCreateGraphCmd.m_Graph->getGraphNode(end_row, end_col);
    graphPathFinderASTARStrategyInput.m_Strategy = PathFindingSTrategy::NonGreedyASTAR;

    auto graphPathFinderCommandDFSStrategy = CommandsManager::GetInstance()->GetCommand("GraphPathFinderCommand");
    // Set Input to the command GraphPathFinderCommand with DFS strategy
    graphPathFinderCommandDFSStrategy->SetData(std::any(graphPathFinderASTARStrategyInput));
    // Execute the command GraphPathFinderCommand with DFS strategy
    graphPathFinderCommandDFSStrategy->Execute();
    // Fetch the output from the command GraphPathFinderCommand with DFS strategy
    auto anyPathFinderCmdNonGreedyASTAROutput = std::any(pathFinderCmdNonGreedyASTAROutput);
    graphPathFinderCommandDFSStrategy->GetData(anyPathFinderCmdNonGreedyASTAROutput);
    pathFinderCmdNonGreedyASTAROutput = std::any_cast<GraphPathFinderOutput>(anyPathFinderCmdNonGreedyASTAROutput);

    std::cout << "\n Feasible solution Path in ASTAR strategy is" << std::endl;
    outputFromCreateGraphCmd.m_Graph->printPaths(pathFinderCmdNonGreedyASTAROutput.m_AllSolutionPaths);

    if (pathFinderCmdNonGreedyASTAROutput.m_containsCycles)
    {
        std::cout << "\n **The Graph contains one or more cycles **" << std::endl;
    }

    bool containsCycles = false;
    if (pathFinderCmdNonGreedyASTAROutput.m_containsCycles)
    {
        std::cout << "\n **The Graph contains one or more cycles **" << std::endl;
        containsCycles = true;
    }

    for (int ii = 0; ii < pathFinderCmdNonGreedyASTAROutput.m_AllSolutionPaths.size(); ii++)
    {
        std::vector<std::tuple<int, int>> solutionPath;
        for (int jj = 0; jj < pathFinderCmdNonGreedyASTAROutput.m_AllSolutionPaths[ii].size(); jj++)
        {
            auto graphPathCoord = pathFinderCmdNonGreedyASTAROutput.m_AllSolutionPaths[ii][jj];
            auto coord = std::make_tuple<int, int>(graphPathCoord->getRow(), graphPathCoord->getCol());
            solutionPath.push_back(coord);
        }
        allSolutionPaths.push_back(solutionPath);
    }

    result = new std::tuple< std::vector<std::vector<std::tuple<int, int>>>, bool >(allSolutionPaths, containsCycles);
    return result;
}