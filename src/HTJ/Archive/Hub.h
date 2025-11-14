#ifndef HubData
#define HubData

#include <iostream>
#include <string>
#include "SimpleMap.h"

struct PersonalData
{
    std::string Username;
    // std::vector<std::string> Userlist;
};

class CoreData
{
public:
    PersonalData Target;

    bool lifetime = true;
    bool scaning = false;
    bool thief = false;

    std::queue<STRING> Q_Directories;
    std::queue<STRING> Q_Files;
    AJimpa::SimpleMap<STRING, bool> L_Drivers;
    AJimpa::SimpleMap<STRING, int> L_Folder;
    std::vector<std::string> L_Files;

public:
    CoreData(/* args */){};
    ~CoreData(){};
};

#endif  // HubData
