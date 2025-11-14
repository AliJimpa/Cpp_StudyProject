#pragma once
#include "Object.h"
#include "Multiplier.h"
#include "Application.h"

class App : public Object
{
public:
    void OnBegin() override
    {
    }
    void OnUpdate() override
    {
        STRING argoment;
        GET(argoment);
        if (argoment == "Quit")
        {
            Quit();
            return;
        }
        if (argoment == "quit")
        {
            Quit();
            return;
        }
        if(argoment == "Multi")
        {
            CREATEOBJECT(Multiplier);
            return;
        }
        PRINT(argoment << ": NotDefine");
    }
    void OnEnd() override
    {
    }
};