#pragma once

#include "ICommand.h"
#include "InputOutput.h"
#include "NonGreedyASTARStrategyPathFinder.h"
#include "DFSStrategyPathFinder.h"

template <typename GraphPathFinderInputType, typename GraphPathFinderOutputType>
class GraphPathFinderCommandExecutor
{
private:
    std::optional<GraphPathFinderInputType> m_InputData = std::nullopt;
    std::optional<GraphPathFinderOutputType> m_OutputData = std::nullopt;
public:
    GraphPathFinderCommandExecutor() {}
    ~GraphPathFinderCommandExecutor() {}
    void SetInput(const GraphPathFinderInputType& data)
    {
        m_InputData = std::make_optional(data);
    }
    std::optional<GraphPathFinderOutputType> GetOutput()
    {
        return m_OutputData;
    }
    bool RunExecute()
    {
        GraphPathFinderOutputType outData;
        auto graph = CommandsManager::GetGraph();

        std::vector<GraphNode<Node>*> solutonPath;
        if (m_InputData.value().m_Strategy == PathFindingSTrategy::NonGreedyASTAR)
        {
            if (m_InputData.value().m_EndNode && m_InputData.value().m_EndNode)
            {
                outData.m_AllPaths = outData.m_AllSolutionPaths = NonGreedyASTARStrategyPathFinder::FindPath<GraphNode<Node>, Node>(graph,
                    std::nullopt, m_InputData.value().m_StartNode,
                    m_InputData.value().m_EndNode,
                    outData.m_containsCycles);
            }
            else
                return false;
        }
        else if (m_InputData.value().m_Strategy == PathFindingSTrategy::DFS)
        {
            if (m_InputData.value().m_StartNode)
            {
                DFSStrategyPathSolutionFinder::FindPaths<GraphNode<Node>, Node>(graph, std::nullopt,
                    m_InputData.value().m_StartNode,
                    outData.m_AllPaths,
                    outData.m_AllSolutionPaths,
                    outData.m_containsCycles);
            }
            else
                return false;
        }
        
        m_OutputData = std::make_optional(outData);
        std::cout << "\nGraph Path Finder command Executed" << std::endl;
        return true;
    }

    bool PreExecuteSequence(){ return true;}
    bool PostExecuteSequence(){return true;}
    bool PreExecuteCommand(){return true;}
    bool PostExecuteCommand(){return true;}
};


