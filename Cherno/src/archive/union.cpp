#include <iostream>

#define LOG(x) std::cout << x << std::endl;

union tr{
    float xz;
    int yz;
};


void MyPrinter(tr& a ){
    std::cout << a.xz << " || " << a.yz << std::endl;
}

int main()
{

    union tr test;
    test.xz = 50.3f;
    test.yz = 3400;
    MyPrinter(test);
    test.xz = 89.3f;
    MyPrinter(test);
    test.yz = 9900;
    LOG(test.xz);
    LOG(test.yz);

    std::cin.get();

}
