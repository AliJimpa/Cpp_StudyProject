#include "pch.h"
#include "Casting.Cpp"

//#define LOG(x) std::cout << x << std::endl

int main()
{
    Lion L1;
    Animal AT = (Animal)L1;
    L1.SetValue(8, 13);
    LOG(AT.GetValue(0));

    std::cin.get();
}