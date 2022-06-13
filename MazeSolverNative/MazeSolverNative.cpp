// MazeSolverNative.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "MazeSolverNative.h"


// This is an example of an exported variable
MAZESOLVERNATIVE_API int nMazeSolverNative=0;

// This is an example of an exported function.
MAZESOLVERNATIVE_API int fnMazeSolverNative(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CMazeSolverNative::CMazeSolverNative()
{
    return;
}
