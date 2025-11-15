#include <iostream>
#include <array>
#include <string>
#include <functional>

#include <vector>
#include <algorithm>

#define PRINT(text) std::cout << text << std::endl

void ForEach(const std::vector<int>& values , const std::function<void(int)>& func)
{
   for(int value : values)
   {
      func(value);
   }
}


int main()
{
   std::vector<int> myvalue = {5,6,25,6,9,7,8,1,6454,55};
   int add = 1;
   auto mylambda = [=](int item){PRINT(item + add);} ;
   ForEach(myvalue , mylambda);
}