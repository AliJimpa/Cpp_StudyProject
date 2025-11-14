#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <random>

namespace AJimpa
{

    std::string GetSystemUsername()
    {
        char *username = nullptr;
        size_t len = 0;
        errno_t err = _dupenv_s(&username, &len, "USERNAME");

        if (err == 0 && username != nullptr)
        {
            std::string result(username);
            free(username);
            return result;
        }
        else
        {
            std::cerr << "Failed to get username from environment variables." << std::endl;
            return "";
        }
    }

    std::wstring GetSystemUsernameW()
    {
        wchar_t *username = nullptr;
        size_t len = 0;
        errno_t err = _wgetenv_s(&len, nullptr, 0, L"USERNAME");

        if (len == 0)
        {
            std::wcerr << L"USERNAME environment variable is not set." << std::endl;
            return L"";
        }

        username = new wchar_t[len];
        err = _wgetenv_s(&len, username, len, L"USERNAME");

        if (err == 0 && username != nullptr)
        {
            std::wstring result(username);
            delete[] username;
            return result;
        }
        else
        {
            std::wcerr << L"Failed to get username from environment variables." << std::endl;
            if (username != nullptr)
            {
                delete[] username;
            }
            return L"";
        }
    }

    std::string GetTime()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm;
        localtime_s(&now_tm, &now_time_t);

        std::ostringstream oss;
        oss << std::put_time(&now_tm, "%H%M%S");
        return oss.str();
    }

    std::string GetCurrentDate()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm;
        localtime_s(&now_tm, &now_time_t);

        std::ostringstream oss;
        oss << std::put_time(&now_tm, "%Y%m%d");
        return oss.str();
    }

    std::wstring GetCurrentDateW()
    {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm tm_now;
        localtime_s(&tm_now, &time_t_now);
        std::wstringstream wss;
        wss << std::put_time(&tm_now, L"%Y%m%d");
        return wss.str();
    }

    std::wstring GetTimeW()
    {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm tm_now;
        localtime_s(&tm_now, &time_t_now);
        std::wstringstream wss;
        wss << std::put_time(&tm_now, L"%H%M%S");
        return wss.str();
    }

    bool getRandomBoolean()
    {
        // Create a random device to seed the random number generator
        std::random_device rd;
        // Use the Mersenne Twister engine for random number generation
        std::mt19937 gen(rd());
        // Create a uniform distribution that returns 0 or 1
        std::uniform_int_distribution<> dis(0, 1);
        // Return a boolean value based on the random number generated
        return dis(gen) == 1;
    }
}