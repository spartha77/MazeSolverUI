#pragma once
#include <vector>
#include <memory>
#include <map>
#include "IDirective.h"
#include "CommandsFactory.h"
#include "MultitypeObjectsContainer.h"
#include "Node.h"
#include "Graph.h"

class CommandsManager
{
private:
    CommandsManager() 
    {
        m_Graph = std::make_unique<Graph<GraphNode<Node>, Node>>(Graph<GraphNode<Node>, Node>());
    }

    std::map<std::string, IDirective*> m_CommandsMap;
    MultiVector m_CommandsMultiVector;

    inline static std::unique_ptr<CommandsManager> m_CommandsManagerInstance;
    inline static std::unique_ptr< Graph<GraphNode<Node>, Node>> m_Graph;

public:
    ~CommandsManager() {}

    static CommandsManager*
        GetInstance()
    {
        static std::once_flag onceFlag;
        std::call_once(onceFlag, [&]() {
            m_CommandsManagerInstance.reset(new CommandsManager());
            std::cout << "CommandsManager's instance created" << std::endl;
            });
        return m_CommandsManagerInstance.get();
    }
    static Graph<GraphNode<Node>, Node>* GetGraph()
    {
        return GetInstance()->m_Graph.get();
    }
    template<typename CommandInputDataType, typename CommandOutputDataType, typename CommandExecutorType>
    ICommand<CommandInputDataType, CommandOutputDataType>*
        CreateCommand(const std::string& commandName, CommandExecutorType& executor)
    {
        auto command = CommandsFactory::CreateCommand<CommandInputDataType,
            CommandOutputDataType, CommandExecutorType>(commandName, executor);
        m_CommandsMap[commandName] = command;
        m_CommandsMultiVector.add(command);
        return command;
    }

    IDirective* GetCommand(const std::string& commandName)
    {
        if (m_CommandsMap.find(commandName) != m_CommandsMap.end())
        {
            return m_CommandsMap[commandName];
        }
        return nullptr;
    }

    template <typename CommandInputDataType, typename CommandOutputDataType>
    ICommand< CommandInputDataType, CommandOutputDataType>* GetCommand()
    {
        auto cmds = m_CommandsMultiVector.all< CommandInputDataType, CommandOutputDataType>();
        if (!cmds.empty())
            return cmds[0];
        return nullptr;
    }
};


