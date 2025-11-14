#pragma once

#include "UserInterface.h"
#include "App.h"

class UILauncher : public UserInterface
{
public:
    UILauncher(App *owner);
};