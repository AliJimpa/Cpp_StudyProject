#pragma once
#include "Object.h"

class Multiplier : public Object
{
public:
    Multiplier()
    {
        tick = false;
    }
    void OnBegin() override
    {
        PRINT("/////////////////////  Multiplier");
        int value;
        INPUT("Number", value);
        std::cout << "You entered: " << value << std::endl;
        PRINT(REMOVEOBJECT(this));
    }
    void OnUpdate() override
    {
    }
    void OnEnd() override
    {
    }
};