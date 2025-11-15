#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "JimpaLibrary.h"

void GetFileListing(const std::string &directory, const std::string &fileFilter, std::ofstream &outFile, bool recursively = true)
{
    if (recursively)
    {
        // First, call the function non-recursively to list files in the current directory
        GetFileListing(directory, fileFilter, outFile, false);
    }

    std::string searchPath = directory + "\\" + (recursively ? "*" : fileFilter);

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error: Unable to open directory " << directory << std::endl;
        return;
    }

    do
    {
        // Skip "." and ".." directories
        if (std::string(findFileData.cFileName) == "." || std::string(findFileData.cFileName) == "..")
        {
            continue;
        }

        std::string filePath = directory + "\\" + findFileData.cFileName;

        if (!recursively)
        {
            // Write the file path to the output file if not in recursive mode
            outFile << filePath << std::endl;
        }
        else
        {
            // Recursively list files in subdirectories
            if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
            {
                GetFileListing(filePath, fileFilter, outFile);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    DWORD dwError = GetLastError();
    FindClose(hFind);
    if (dwError != ERROR_NO_MORE_FILES)
    {
        std::cerr << "FindNextFile error. Error code: " << dwError << std::endl;
    }
}

int main()
{
    STRING directory = "C:\\your_directory";
    STRING fileFilter = "*";
    STRING outputFile  = "file_listing.txt";

    Request("Writeyourpath", directory);
    Request("WriteOutptname", outputFile);

    std::ofstream outFile(outputFile);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open output file " << outputFile << std::endl;
        return 1;
    }
    GetFileListing(directory, fileFilter, outFile);
    outFile.close();
    std::cout << "File listing written to " << outputFile << std::endl;


    std::cin.get();
    return 0;
}