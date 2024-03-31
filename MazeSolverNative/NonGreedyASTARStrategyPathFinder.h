#pragma once
#include <vector>
#include <optional>
#include <functional>
#include "Graph.h"

class NonGreedyASTARStrategyPathFinder
{
public:
    template<typename GraphNodeType, typename NodeType>
    static std::vector<std::vector<GraphNodeType*>> FindPath(Graph<GraphNodeType, NodeType>* graph,
        std::optional<std::function<void(GraphNodeType*)>> visitor_fn_opt,
        GraphNodeType *startGraphNode, GraphNodeType *endGraphNode,
        bool &containsCycle)
    {
        std::vector<std::vector<GraphNodeType*>> res;
        graph->setHeuristicValues(endGraphNode);
        auto nonGreedyASTARPath = graph->findPathUsingNonGreedyASTAR(startGraphNode, endGraphNode,
            containsCycle );
        res.push_back(nonGreedyASTARPath);
        return res;
    }
};


