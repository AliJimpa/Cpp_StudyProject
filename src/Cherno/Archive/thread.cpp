#include <iostream>
#include <thread>

#define LOG(x) std::cout << x << std::endl
#define TLOG(x) std::cout << x << "  ->" << std::this_thread::get_id() << std::endl
#define CLICK std::cin.get()

static bool S_Finish = false;

void DoWork()
{
    using namespace std::literals::chrono_literals;

    while (!S_Finish)
    {
        TLOG( "Working..." );
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    std::thread MyWorker(DoWork);

    CLICK;
    S_Finish = true;

    MyWorker.join();

    TLOG("DONE");
}


