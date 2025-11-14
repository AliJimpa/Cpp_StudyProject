#ifndef THREADSAFECOUNTER_H
#define THREADSAFECOUNTER_H

#include <iostream>
#include <mutex>
#include <string>
#include "SimpleMap.h"

// Hash function to convert a string to an integer
constexpr unsigned int hashString(const char *str, int h = 0)
{
    return !str[h] ? 5381 : (hashString(str, h + 1) * 33) ^ str[h];
}

struct PersonalData
{
    std::string Username;
    // std::vector<std::string> Userlist;
};

class ThreadSafeCounter
{
private:
    mutable std::mutex mtx;
    PersonalData Target;
    bool scaning = false;                      // Scanning
    bool thief = false;                        // Thief
    std::queue<STRING> Q_Directories;          // Directory
    std::queue<STRING> Q_Files;                // File
    std::queue<STRING> Q_Message;              // Message
    AJimpa::SimpleMap<STRING, bool> L_Drivers; // DriversList
    AJimpa::SimpleMap<STRING, int> L_Folder;   // FolderList
    std::vector<std::string> L_Files;          // FileList

public:
    ThreadSafeCounter(){};
    ~ThreadSafeCounter(){};

    PersonalData &GetTarget()
    {
        return Target;
    }

    void SetValue(const std::string &name, bool value)
    {
        std::lock_guard<std::mutex> guard(mtx);
        switch (hashString(name.c_str()))
        {
        case hashString("Scanning"):
            scaning = value;
            break;
        case hashString("Thief"):
            thief = value;
            break;
        default:
            std::cout << "Variable name not found" << std::endl;
            break;
        }
    }

    bool GetValue(const std::string &name) const
    {
        std::lock_guard<std::mutex> guard(mtx);
        switch (hashString(name.c_str()))
        {
        case hashString("Scanning"):
            return scaning;
        case hashString("Thief"):
            return thief;
        default:
            std::cout << "Variable name not found" << std::endl;
            return false;
        }
    }

    std::queue<STRING> &GetValueQueue(const std::string &name)
    {
        std::lock_guard<std::mutex> guard(mtx);
        switch (hashString(name.c_str()))
        {
        case hashString("Directory"):
            return Q_Directories;
        case hashString("File"):
            return Q_Files;
        case hashString("Message"):
            return Q_Message;
        default:
            std::cout << "Variable name not found" << std::endl;
            return Q_Message;
        }
    }

    AJimpa::SimpleMap<STRING, bool> &GetValueMapB(const std::string &name)
    {
        std::lock_guard<std::mutex> guard(mtx);
        switch (hashString(name.c_str()))
        {
        case hashString("DriversList"):
            return L_Drivers;
        default:
            std::cout << "Variable name not found" << std::endl;
            return L_Drivers;
        }
    }

    AJimpa::SimpleMap<STRING, int> &GetValueMapI(const std::string &name)
    {
        std::lock_guard<std::mutex> guard(mtx);
        switch (hashString(name.c_str()))
        {
        case hashString("FolderList"):
            return L_Folder;
        default:
            std::cout << "Variable name not found" << std::endl;
            return L_Folder;
        }
    }

    std::vector<std::string> &GetValueArry(const std::string &name)
    {
        std::lock_guard<std::mutex> guard(mtx);
        switch (hashString(name.c_str()))
        {
        case hashString("FileList"):
            return L_Files;
        default:
            std::cout << "Variable name not found" << std::endl;
            return L_Files;
        }
    }
};
#endif // THREADSAFECOUNTER_H
