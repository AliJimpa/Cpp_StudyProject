#include <iostream>

#define LOG(x) std::cout << x << std::endl

class Animal
{
private:
    float x, y;

public:

    void SetValue(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    float GetValue(int index)
    {
        switch (index)
        {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        default:
            return -100;
            break;
        }
    }
    
    Animal(/* args */)
    {
    }

    ~Animal()
    {
    }
};

class Lion : public Animal
{
private:
    /* data */
public:
    Lion(/* args */)
    {
    }
    ~Lion()
    {
    }
};

class Horse : public Animal
{
private:
    /* data */
public:
    Horse(/* args */)
    {
    }
    ~Horse()
    {
    }
};

// int main()
// {
//     Lion L1;
//     Animal AT = (Animal)L1;
//     L1.SetValue(8, 13);
//     LOG(AT.GetValue(0));

//     std::cin.get();
// }