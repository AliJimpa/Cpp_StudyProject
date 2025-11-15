#pragma once

#include <iostream>
#include <windows.h>
#include <queue>
#include "AJ_Macro.h"

namespace AJimpa
{

    void listDirectories(const std::string &directoryPath, std::queue<STRING> *Targetque)
    {
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile((directoryPath + "/*").c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Invalid file handle. Error is " << GetLastError() << std::endl;
        }
        else
        {
            do
            {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0)
                    {
                        Targetque->push(directoryPath + "\\" + findFileData.cFileName);
                        // std::string fullPath = directoryPath + "\\" + findFileData.cFileName;
                        // std::cout << fullPath << std::endl;
                    }
                }
            } while (FindNextFile(hFind, &findFileData) != 0);
            FindClose(hFind);
        }
    }

    void listFiles(const std::string &directoryPath, std::queue<STRING> *Targetque)
    {
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile((directoryPath + "\\*").c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Invalid file handle. Error is " << GetLastError() << std::endl;
        }
        else
        {
            do
            {
                // Check if it's not a directory (i.e., it's a file)
                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    Targetque->push(directoryPath + "\\" + findFileData.cFileName);
                    // std::string fullPath = directoryPath + "\\" + findFileData.cFileName;
                    // std::cout << fullPath << std::endl;
                }
            } while (FindNextFile(hFind, &findFileData) != 0);
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

    void PrintDriveInfo(const std::string& drive) {
    UINT driveType = GetDriveType(drive.c_str());
    switch (driveType) {
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


}