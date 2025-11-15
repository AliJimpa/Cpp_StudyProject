#pragma once
#include <iostream>

// Variable
bool bAppRuning = true;

// Macro
#define INPUT(n, x)        \
    std::cout << n << ">"; \
    std::cin >> x
#define GET(x)      \
    std::cout << ">"; \
    std::cin >> x
#define PRINT(x) std::cout << x << std::endl
#define CREATEOBJECT(x) SpawnObject<x>()
#define REMOVEOBJECT(x) DespawnObject(x)
#define STRING std::string

// define 
void Quit();
