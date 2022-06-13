#pragma once
#include "InputOutput.h"
#include "GraphCreationCommandExecutor.h"
#include "GraphPathFinderCommandExecutor.h"
#include "CommandsManager.h"

GraphCreationCommandExecutor<GraphCreationCommandInput, GraphCreationCommandOutput> graphCreationCommandExecutor;
GraphPathFinderCommandExecutor<GraphPathFinderInput, GraphPathFinderOutput> graphPathFinderCommandExecutor;
void Init()
{
    auto cmd = CommandsManager::GetInstance()->CreateCommand< GraphCreationCommandInput, GraphCreationCommandOutput,
        GraphCreationCommandExecutor<GraphCreationCommandInput, GraphCreationCommandOutput> >("GraphCreationCommand", graphCreationCommandExecutor);

    auto cmd2 = CommandsManager::GetInstance()->CreateCommand< GraphPathFinderInput, GraphPathFinderOutput,
        GraphPathFinderCommandExecutor<GraphPathFinderInput, GraphPathFinderOutput> >("GraphPathFinderCommand", graphPathFinderCommandExecutor);
}

