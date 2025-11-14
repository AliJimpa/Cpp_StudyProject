#include <iostream>
#include <chrono>
#include <thread>

#define TLOG(x) std::cout << x << "  ->" << std::this_thread::get_id() << std::endl
#define NOW() std::chrono::high_resolution_clock::now()


struct Timer
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        end =std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        std::cout<< "Timer took " << ms << " ms" << std::endl;
    }
};

void CustomFunction()
{
    Timer mytimer;

    for (size_t i = 0; i < 100; i++)
    {
        std::cout << "Hello\n";
    }
    
}

int main()
{
    CustomFunction();

    std::cin.get();
}