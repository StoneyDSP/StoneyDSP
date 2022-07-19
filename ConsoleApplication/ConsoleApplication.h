// ConsoleApplication.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.

#include "Atomic.h"
#include "UniquePointer.h"
#include "Value.h"
//#include "X.h"

void intro()
{
    std::cout << "Hello CMake World!" << std::endl;
    std::cout << std::endl;
}

void outro()
{
    std::cout << "Goodbye CMake World!" << std::endl;
    std::cout << std::endl;
}

void lineBreak()
{
    std::cout << "//============================================================================//" << std::endl;
}

void newLine()
{
    std::cout << std::endl;
}

void wait()
{
    std::cin.get();
}
