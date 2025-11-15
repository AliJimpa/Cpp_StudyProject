#pragma once
#include "Object.h"

class MultiplierObj : public Object
{
public:
    MultiplierObj()
    {
        tick = false;
    }
    void OnBegin() override
    {
        PRINT("/////////////////////  Multiplier");
        int value1 , value2;
        INPUT("Number A", value1);
         INPUT("Number B", value2);
        std::cout << "You entered: " << value1 * value2 << std::endl;
        PRINT(REMOVEOBJECT(this));
    }
    void OnUpdate() override
    {
    }
    void OnEnd() override
    {
    }
};