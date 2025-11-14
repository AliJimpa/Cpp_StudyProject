#pragma once

#include <iostream>
#include <filesystem>
#include <locale>
#include <windows.h>

#include <string>
#include <queue>
#include "AJ_Macro.h"

namespace AJimpa
{

    void listDirectories(const std::wstring &directoryPath, std::queue<std::wstring> *Targetque)
    {
        WIN32_FIND_DATAW findFileData;
        HANDLE hFind = FindFirstFileW((directoryPath + L"\\*").c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            std::wcerr << L"Invalid file handle. Error is " << GetLastError() << std::endl;
        }
        else
        {
            do
            {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0)
                    {
                        Targetque->push(directoryPath + L"\\" + findFileData.cFileName);
                    }
                }
            } while (FindNextFileW(hFind, &findFileData) != 0);
            FindClose(hFind);
        }
    }

    void listFiles(const std::wstring &directoryPath, std::queue<std::wstring> *Targetque)
    {
        WIN32_FIND_DATAW findFileData;
        HANDLE hFind = FindFirstFileW((directoryPath + L"\\*").c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            std::wcerr << L"Invalid file handle. Error is " << GetLastError() << std::endl;
        }
        else
        {
            do
            {
                // Check if it's not a directory (i.e., it's a file)
                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    Targetque->push(directoryPath + L"\\" + findFileData.cFileName);
                }
            } while (FindNextFileW(hFind, &findFileData) != 0);
            FindClose(hFind);
        }
    }

    std::vector<std::string> GetListLogicalDrive()
    {
        std::vector<std::string> drives;
        DWORD driveMask = GetLogicalDrives();
        if (driveMask == 0)
        {
            std::cerr << "GetLogicalDrives() failed with error code: " << GetLastError() << std::endl;
            return drives;
        }

        char driveLetter = 'A';
        while (driveMask)
        {
            if (driveMask & 1)
            {
                std::string drive(1, driveLetter);
                drive.append(":\\");
                drives.push_back(drive);
            }
            driveMask >>= 1;
            driveLetter++;
        }
        return drives;
    }

    std::vector<std::wstring> GetListLogicalDrivew()
    {
        std::vector<std::wstring> drives;
        DWORD driveMask = GetLogicalDrives();
        if (driveMask == 0)
        {
            std::wcerr << L"GetLogicalDrives() failed with error code: " << GetLastError() << std::endl;
            return drives;
        }

        wchar_t driveLetter = L'A';
        while (driveMask)
        {
            if (driveMask & 1)
            {
                std::wstring drive(1, driveLetter);
                drive.append(L":\\");
                drives.push_back(drive);
            }
            driveMask >>= 1;
            driveLetter++;
        }
        return drives;
    }

    void PrintDriveInfo(const std::string &drive)
    {
        UINT driveType = GetDriveType(drive.c_str());
        switch (driveType)
        {
        case DRIVE_UNKNOWN:
            std::cout << drive << " - Unknown drive type" << std::endl;
            break;
        case DRIVE_NO_ROOT_DIR:
            std::cout << drive << " - No root directory" << std::endl;
            break;
        case DRIVE_REMOVABLE:
            std::cout << drive << " - Removable drive" << std::endl;
            break;
        case DRIVE_FIXED:
            std::cout << drive << " - Fixed drive" << std::endl;
            break;
        case DRIVE_REMOTE:
            std::cout << drive << " - Remote (network) drive" << std::endl;
            break;
        case DRIVE_CDROM:
            std::cout << drive << " - CD-ROM drive" << std::endl;
            break;
        case DRIVE_RAMDISK:
            std::cout << drive << " - RAM disk" << std::endl;
            break;
        default:
            std::cout << drive << " - Unknown drive type" << std::endl;
            break;
        }
    }

    std::wstring stringToWString(const std::string &s)
    {
        int len;
        int slength = static_cast<int>(s.length()) + 1;
        len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, 0, 0); // Get the length of the result
        wchar_t *buf = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, buf, len);
        std::wstring r(buf);
        delete[] buf;
        return r;
    }

    std::string wstringToString(const std::wstring &ws)
    {
        if (ws.empty())
            return std::string();

        int len = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string s(len, '\0');
        WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, &s[0], len, nullptr, nullptr);
        s.pop_back(); // Remove the null terminator
        return s;
    }

    bool compareNames(const std::string &name1, const std::string &name2)
    {
        if (name1.size() != name2.size())
        {
            return false;
        }
        return std::equal(name1.begin(), name1.end(), name2.begin(),
                          [](char a, char b)
                          {
                              return tolower(a) == tolower(b);
                          });
    }

    bool findMatches(const std::vector<std::string> &List, const std::string &target)
    {
        bool matches = false;
        for (const auto &name : List)
        {
            if (compareNames(name, target))
            {
                matches = true;
            }
        }
        return matches;
    }

}