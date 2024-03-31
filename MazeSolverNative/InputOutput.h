#pragma once

#pragma once
#include <string>
#include "GraphNode.h"

enum class PathFindingSTrategy
{
    DFS,
    NonGreedyASTAR
};

struct GraphCreationCommandInput { std::string m_data = "GraphCreationCommandInput"; };
struct GraphCreationCommandOutput 
{ 
    std::string m_data = "GraphCreationCommandOutput"; 
    std::vector<GraphNode<Node>*> m_EndNodes;
    Graph<GraphNode<Node>, Node>* m_Graph;
};


struct GraphPathFinderInput
{
    std::string m_data = "GraphPathFinderInput";
    GraphNode<Node>* m_StartNode = nullptr;
    GraphNode<Node>* m_EndNode = nullptr;
    PathFindingSTrategy m_Strategy = PathFindingSTrategy::DFS;    
};

struct GraphPathFinderOutput
{
    std::string m_data = "GraphPathFinderOutput";
    std::vector<std::vector<GraphNode<Node>*>> m_AllPaths;
    std::vector<std::vector<GraphNode<Node>*>> m_AllSolutionPaths;
    bool m_containsCycles = false;
};






