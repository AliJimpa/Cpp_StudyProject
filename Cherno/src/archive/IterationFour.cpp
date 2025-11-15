#include <iostream>
#include <string>
#include <unordered_map>

#define PRINT(text) std::cout << text << std::endl


#ifdef PREDEBUG
#define MYLOG(Y) std::cout << Y << std::endl
#else
#define MYLOG(Y) std::cout<< "FUCK" << std::endl
#endif


using CustomList = std::unordered_map<int,std::string>;

// int main()
// {
//    CustomList ali = { {2,"Hello"} , {5,"fuckyou"}};
//    ali.insert( {66,"TRTR"} );
//    for(auto& item : ali)
//    {
//       std::cout<< item.first << " - " << item.second << std::endl;
//    }
//    ali.
//    MYLOG("Ali");
// }