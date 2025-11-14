#pragma once

#include <iostream>
#include <filesystem>

// Disable specific warnings temporarily
#pragma warning(push)
#pragma warning(disable : 4996) // Disable deprecated functions warning

// Define CP_UTF8 if it's not already defined
#ifndef CP_UTF8
#define CP_UTF8 65001
#endif

namespace AJimpa
{

    struct AJ_Path
    {
    public:
        std::wstring Fullpath;
        std::wstring Parentpath;
        std::wstring Filename;
        std::wstring Filetype;

        void print()
        {
            std::wcout << L"Fullpath: " << Fullpath << std::endl;
            std::wcout << L"Parentpath: " << Parentpath << std::endl;
            std::wcout << L"Filename: " << Filename << std::endl;
            std::wcout << L"Filetype: " << Filetype << std::endl;
        }
    };

    bool IsDirectoryExists(std::string &directorypath)
    {
        if (std::filesystem::exists(directorypath) && std::filesystem::is_directory(directorypath))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool IsFileExists(const std::string &filename)
    {
        return std::filesystem::exists(filename);
    }

    bool CreateDirectory(std::string path)
    {
        try
        {
            if (std::filesystem::create_directory(path))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
            return false;
        }
    }

    bool CreateDirectoryw(const std::wstring &path)
    {
        try
        {
            // std::filesystem::path constructor accepts std::wstring
            if (std::filesystem::create_directory(std::filesystem::path(path)))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::wcerr << L"Filesystem error: " << e.what() << std::endl;
            return false;
        }
    }

    bool CreateDirectory(std::string &path, std::string &Name)
    {
        std::string folderpath = path + "\\" + Name;
        try
        {
            if (std::filesystem::create_directory(path))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
            return false;
        }
    }

    void listFilesInDirectory(const std::string &path)
    {
        try
        {
            for (const auto &entry : std::filesystem::directory_iterator(path))
            {
                std::cout << entry.path().string() << std::endl;
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }
    }

    std::filesystem::path getApplicationPath()
    {
        char path[MAX_PATH];
        HMODULE hModule = GetModuleHandle(nullptr);
        if (hModule != nullptr)
        {
            GetModuleFileName(hModule, path, MAX_PATH);
            return std::filesystem::path(path);
        }
        else
        {
            std::cerr << "Failed to get module handle. Error code: " << GetLastError() << std::endl;
            return "";
        }
    }

    AJ_Path splitPath(const std::filesystem::path &fullPath)
    {
        std::filesystem::path parentPath = fullPath.parent_path();
        std::filesystem::path filename = fullPath.filename();
        std::filesystem::path filetype = fullPath.extension();
        AJ_Path packagepath;
        packagepath.Fullpath = fullPath.wstring();
        packagepath.Parentpath = parentPath.wstring();
        packagepath.Filename = filename.wstring();
        packagepath.Filetype = filetype.wstring();
        return packagepath;
    }

    // Function to write to a file
    void writeToFile(const std::wstring &filePath, const std::wstring &text)
    {
        std::wofstream outFile(filePath, std::ios::out | std::ios::app);
        if (!outFile.is_open())
        {
            std::wcerr << L"Failed to open file for writing: " << filePath << std::endl;
            return;
        }

        // Set the locale to UTF-8
        outFile.imbue(std::locale(outFile.getloc(), new std::codecvt_utf8<wchar_t>));
        outFile << text << std::endl;
        outFile.close();
    }

    // Function to read from a file
    void readFromFile(const std::wstring &filePath)
    {
        std::wifstream inFile(filePath);
        if (!inFile.is_open())
        {
            std::wcerr << L"Failed to open file for reading: " << filePath << std::endl;
            return;
        }

        // Set the locale to UTF-8
        inFile.imbue(std::locale(inFile.getloc(), new std::codecvt_utf8<wchar_t>));
        std::wstring line;
        while (std::getline(inFile, line))
        {
            std::wcout << line << std::endl;
        }

        inFile.close();
    }

    // Function to read a single line from a file
    std::wstring readSingleLineFromFile(const std::wstring &filePath, int lineNumber)
    {
        std::wifstream inFile(filePath);
        if (!inFile.is_open())
        {
            std::wcerr << L"Failed to open file for reading: " << filePath << std::endl;
            return L"";
        }

        // Set the locale to UTF-8
        inFile.imbue(std::locale(inFile.getloc(), new std::codecvt_utf8<wchar_t>));
        std::wstring line;
        int currentLine = 0;
        while (std::getline(inFile, line))
        {
            if (currentLine == lineNumber)
            {
                inFile.close();
                return line;
            }
            currentLine++;
        }

        inFile.close();
        std::wcerr << L"Line number " << lineNumber << L" not found in file: " << filePath << std::endl;
        return L"";
    }

    void ScanesFile(const std::wstring &filePath, std::vector<std::string> &List)
    {
        std::wifstream inFile(filePath);
        if (!inFile.is_open())
        {
            std::wcerr << L"Failed to open file for reading: " << filePath << std::endl;
            return;
        }

        // Set the locale to UTF-8
        inFile.imbue(std::locale(inFile.getloc(), new std::codecvt_utf8<wchar_t>));
        std::wstring line;
        while (std::getline(inFile, line))
        {
            List.push_back(wstringToString(line));
        }

        inFile.close();
    }

    void RemoveFile(std::string path)
    {
        try
        {
            if (std::filesystem::remove(path))
            {
                std::cout << "File deleted successfully.\n";
            }
            else
            {
                std::cout << "File not found.\n";
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error deleting file: " << e.what() << std::endl;
        }
    }

    void copyFileToFolder(const std::wstring &sourceFilePath, const std::wstring &destinationFolder)
    {
        // Ensure the destination folder ends with a backslash
        std::wstring destinationPath = destinationFolder;
        if (destinationPath.back() != L'\\')
        {
            destinationPath += L'\\';
        }

        // Extract the file name from the source file path
        std::wstring fileName = sourceFilePath.substr(sourceFilePath.find_last_of(L"\\") + 1);

        // Construct the destination file path
        destinationPath += fileName;

        // Copy the file
        if (CopyFileW(sourceFilePath.c_str(), destinationPath.c_str(), FALSE))
        {
            // std::wcerr << L"File copied successfully to " << destinationPath << std::endl;
        }
        else
        {
            // std::wcerr << L"Failed to copy file. Error: " << GetLastError() << std::endl;
        }
    }

    std::uintmax_t getFileSize(const std::wstring &filePath)
    {
        try
        {
            return std::filesystem::file_size(filePath);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            return 0;
        }
    }

    std::chrono::system_clock::time_point stringToTimePoint(const std::string &dateString)
    {
        std::tm tm = {};
        std::istringstream ss(dateString);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }

    std::chrono::system_clock::time_point fileTimeToSysTime(const std::filesystem::file_time_type &fileTime)
    {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(fileTime - std::filesystem::file_time_type::clock::now() + system_clock::now());
        return sctp;
    }

    bool isFileBeforeDate(const std::filesystem::path &filePath, const std::chrono::system_clock::time_point &targetDate)
    {
        try
        {
            auto ftime = std::filesystem::last_write_time(filePath);
            auto sctp = fileTimeToSysTime(ftime);
            return sctp < targetDate;
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error accessing file: " << e.what() << '\n';
            return false;
        }
    }

    std::string normalizePath(const std::string &path)
    {
        std::string normalizedPath = path;
        std::string::iterator new_end = std::unique(normalizedPath.begin(), normalizedPath.end(), [](char lhs, char rhs)
                                                    { return (lhs == rhs) && (lhs == '\\' || lhs == '/'); });
        normalizedPath.erase(new_end, normalizedPath.end());
        return normalizedPath;
    }

    std::wstring wnormalizePath(const std::wstring &path)
    {
        std::wstring normalizedPath = path;
        std::wstring::iterator new_end = std::unique(normalizedPath.begin(), normalizedPath.end(), [](wchar_t lhs, wchar_t rhs)
                                                     { return (lhs == rhs) && (lhs == L'\\' || lhs == L'/'); });
        normalizedPath.erase(new_end, normalizedPath.end());
        return normalizedPath;
    }

    bool containsFolder(const std::wstring &path, const std::wstring &folderName)
    {
        std::wstring::size_type pos = path.find(folderName);
        return pos != std::wstring::npos;
    }

}

// Re-enable the warnings that were disabled
#pragma warning(pop)