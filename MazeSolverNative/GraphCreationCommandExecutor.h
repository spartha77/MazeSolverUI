#pragma once

#include "ICommand.h"
#include "InputOutput.h"



template <typename GraphCreationInputType, typename GraphCreationOutputType>
class GraphCreationCommandExecutor
{
private:
    std::optional<GraphCreationInputType> m_InputData = std::nullopt;
    std::optional<GraphCreationOutputType> m_OutputData = std::nullopt;
public:
    GraphCreationCommandExecutor() {}
    ~GraphCreationCommandExecutor() {}
    void SetInput(const GraphCreationInputType& data)
    {
        m_InputData = std::make_optional(data);
    }
    std::optional<GraphCreationOutputType> GetOutput()
    {
        return m_OutputData;
    }
    bool RunExecute()
    {
        auto graph = CommandsManager::GetGraph();
        graph->ReadGraphFromFile(m_InputData.value().m_data);
        GraphCreationOutputType data;
        data.m_EndNodes = graph->GetEndNodes();
        data.m_Graph = graph;
        m_OutputData = std::make_optional(data);

        std::cout << "\nGraph Creation command Executed" << std::endl;
        return true;
    }

    bool PreExecuteSequence()
    {
        //std::cout << "\nPre-Execution of  nGraph Creation Sequence" << std::endl;
        return true;
    }
    bool PostExecuteSequence()
    {
        //std::cout << "\nPost-Execution of nGraph Creation Sequence" << std::endl;
        return true;
    }
    bool PreExecuteCommand()
    {
        //std::cout << "\nPre-Execution of  nGraph Creation Command" << std::endl;
        return true;
    }
    bool PostExecuteCommand()
    {
        //std::cout << "\nPost-Execution of nGraph Creation Command" << std::endl;
        return true;
    }
};

