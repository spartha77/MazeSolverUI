#pragma once

#include <vector>
#include <optional>
#include <functional>
#include "Graph.h"

class DFSStrategyPathSolutionFinder
{
public:
    template<typename GraphNodeType, typename NodeType>
    static void FindPaths(Graph<GraphNodeType, NodeType>* graph,
        std::optional<std::function<void(GraphNodeType*)>> visitor_fn_opt,
        GraphNodeType* startGraphNode,
        std::vector<std::vector<GraphNodeType*>>& allPaths, 
        std::vector<std::vector<GraphNodeType*>>& allSolutionPaths,
        bool &containsCycles)
    {
        std::cout << "DFS maze solver algorithm in progress\n";
        allPaths = graph->DFS(startGraphNode, visitor_fn_opt);
        containsCycles = graph->containsCycles();
        allSolutionPaths = graph->getAllSolutionPaths(allPaths);
        
        //graph->printPaths(allSolutionPaths);
    }
};

