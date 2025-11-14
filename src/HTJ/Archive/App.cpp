#include <windows.h>
#include <string>
#include <iostream>
#include "jimpaLibrary.h"

void GetFileListing(std::string directory, std::string fileFilter, bool recursively = true)
{
  if (recursively)
    GetFileListing(directory, fileFilter, false);

  directory += "\\";

  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = INVALID_HANDLE_VALUE;

  std::string filter = directory + (recursively ? "*" : fileFilter);

  hFind = FindFirstFile(filter.c_str(), &FindFileData);

  if (hFind == INVALID_HANDLE_VALUE)
  {
    return;
  }
  else
  {
    if (!recursively)
    {
      std::cout << directory + std::string(FindFileData.cFileName) << std::endl;
    }

    while (FindNextFile(hFind, &FindFileData) != 0)
    {
      if (!recursively)
      {
        std::cout << directory + std::string(FindFileData.cFileName) << std::endl;
      }
      else
      {
        if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0 && FindFileData.cFileName[0] != '.')
        {
          GetFileListing(directory + std::string(FindFileData.cFileName), fileFilter);
        }
      }
    }

    DWORD dwError = GetLastError();
    FindClose(hFind);
    if (dwError != ERROR_NO_MORE_FILES)
    {
      std::cout << "FindNextFile error. Error is " << dwError << std::endl;
    }
  }
}

int main()
{
  STRING direction;
  STRING fileFilter;
  Request("BaseDirectory", direction);
  Request("Filter", fileFilter);
  GetFileListing(direction,fileFilter,false);
  std::cin.get();
}