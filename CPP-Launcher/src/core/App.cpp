
#include "App.h"
#include "UILauncher.h"

App::App()
{
    MyUI = new UILauncher(this);
    run();
}

bool App::CanLoop() const
{
    return GetUI()->canRender();
}

void App::run()
{
    // Start Applications
    OnStart();

    // Init UserInterface
    if (!GetUI()->init())
        return;

    // Main loop
    while (bIsRun && CanLoop())
    {
        OnLateUpdate();
        GetUI()->render();
        OnUpdate();
    }

    GetUI()->shutdown(); // Cleanup
    OnEnd();
}

void App::Quit()
{
    bIsRun = false;
}
