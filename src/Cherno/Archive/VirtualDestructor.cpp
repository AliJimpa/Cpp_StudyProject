#include <iostream>

#define LOG(x) std::cout<<x<<std::endl
class A
{
private:
    int* RE;
public:
    int* getData(){ return RE; }
    A() { RE = new int[500]; LOG("Construct"); }
    ~A() { delete RE;  LOG("Deconstruct"); }
};

int main()
{
    A Reza;
    for (size_t i = 0; i < 500; i++)
    {
        Reza.getData()[i] = i +100;
        LOG(Reza.getData()[i]);
    }
    
    std::cin.get();
}