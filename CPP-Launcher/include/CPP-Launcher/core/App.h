#pragma once

#include "UserInterface.h"

class App
{
public:
    App();
    UserInterface *GetUI() const { return MyUI; }
    void Quit();

protected:
    virtual void OnStart() {};
    virtual void OnLateUpdate() {};
    virtual void OnUpdate() {};
    virtual void OnEnd() {};
    virtual bool CanLoop() const;

private:
    void run();
    UserInterface *MyUI;
    bool bIsRun = true;
};
