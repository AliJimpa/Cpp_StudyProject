#pragma once
#include "Core.h"

class Object
{
public:
    bool tick = true;
    // virtual ~Object() = default;
    virtual void OnBegin() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnEnd() = 0;
};