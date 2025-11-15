#include <iostream>

#include "AJ_BCL.h"
#include "AJ_Macro.h"

using namespace AJimpa;

void ali(const std::vector<std::string> &args)
{
    (void)args;
    LOG("Hello");
}

void Done(const std::vector<std::string> &args)
{
    (void)args;
    //delete *CLine;
}
void addMath(const std::vector<std::string> &args)
{
    if (args.size() < 3)
    {
        std::cout << "Usage: add <num1> <num2>" << std::endl;
        return;
    }
    int num1 = std::stoi(args[1]);
    int num2 = std::stoi(args[2]);
    std::cout << "Result: " << num1 + num2 << std::endl;
}

int main()
{
    // static BCL CLine = BCL();
    // CLine.AddCommand("RTX", ali);
    // CLine.AddCommand("Done",Done);
    // CLine.AddCommand("Add" , addMath);
    // CLine.Run();

    int x = 5;
    int* ptrx = &x;
    LOG(*ptrx);

    /* code */
    return 0;
}
