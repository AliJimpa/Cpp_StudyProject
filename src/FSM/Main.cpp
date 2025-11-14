#include "Application.h"
#include "App.h"

int main()
{
    App myApp;
    objects.push_back(&myApp);
    Start();
    while (bAppRuning)
    {
        Update();
    }
    Finish();
    return 0;
}
