#pragma once
#include <memory>

#include "ICommand.h"
#include "GenericCommand.h"





class CommandsFactory
{
private:
    CommandsFactory() {}

public:
    template<typename CommandInputDataType, typename CommandOutputDataType, typename CommandExecutorType>
    static ICommand< CommandInputDataType, CommandOutputDataType>*
        CreateCommand(const std::string& commandName, CommandExecutorType& executor)
    {
        auto command = MazeSolver::GenericCommandImplWrapper<CommandInputDataType, CommandOutputDataType, CommandExecutorType>::GenericCommandImplementer::GetInstance(commandName, executor);
        return command;
    }
};

