#include <iostream>
#include <thread>
#include "AJ_Macro.h"
#include "AJ_Text.h"

#include <fstream>
#include <string>

static bool S_Finish = false;

void threadFunction1()
{
    using namespace std::literals::chrono_literals;

    while (!S_Finish)
    {
        LOG( "Working..." );
        std::this_thread::sleep_for(1s);
    }
}

void threadFunction2()
{
    using namespace std::literals::chrono_literals;

    while (!S_Finish)
    {
        LOG( "22Working..." );
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    APPPAUSE;
    S_Finish = true;

    t1.join();
    t2.join();

    LOG("DONE");
}



