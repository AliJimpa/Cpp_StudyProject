
#include <iostream>
#include <windows.h>
#include "AJ_Text.h"
#include "AJ_Scanner.h"
#include "AJ_Macro.h"

using namespace AJimpa;

void Printer(STRING path, ListingChannel mtype)
{
    TextFile gfile("Reza.txt");
    switch (mtype)
    {
    case ListingChannel::Begin:
        LOG("Begen = >" + path);
        break;
    case ListingChannel::File:
        LOG("File = >" + path);
        // myfile.WriteLine(path);
        break;
    case ListingChannel::Folder:
        //F_ListFilesInDirectory(path, true,);
        break;
    case ListingChannel::SystemError:
        LOG("SystemError" + path);
        break;
    case ListingChannel::NotExist:
        LOG("NotFind" + path);
        break;
    case ListingChannel::End:
        LOG("End = >" + path);
        break;
    }
}

// Rename the function to avoid conflict with Windows API
std::vector<std::string> GetLogicalDriveStrings()
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

int main()
{
    std::vector<std::string> drives = GetLogicalDriveStrings();
    for (const auto &drive : drives)
    {
        if (drive != "C:\\")
        {
            F_ListFilesInDirectory(drive, true);
        }
        LOG(drive);
    }
    
    return 0;
}




// void WriteLargeTextFile(const std::string &filePath, const std::string &largeText, std::size_t chunkSize = 1024)
// {
//     std::ofstream outFile(filePath);
//     if (!outFile.is_open())
//     {
//         std::cerr << "Failed to open file for writing: " << filePath << std::endl;
//         return;
//     }

//     // Write the large text in chunks
//     for (std::size_t i = 0; i < largeText.size(); i += chunkSize)
//     {
//         std::size_t len = std::min( chunkSize, (largeText.size() - i) );
//         outFile.write(&largeText[i], len);
//     }

//     // Close the file


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