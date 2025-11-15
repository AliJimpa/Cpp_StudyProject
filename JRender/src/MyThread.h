#pragma once
#include <thread>

static float MyRange = -0.8f;

float random_float(float min, float max)
{
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

void DoWork()
{
    using namespace std::literals::chrono_literals;

    while (true)
    {
        std::cout << "Write Position >> ";
        std::cin >> MyRange;
        //MyRange = random_float(-1,1);
        //std::this_thread::sleep_for(0.2s);
    }
}
