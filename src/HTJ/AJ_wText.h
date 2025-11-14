#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <filesystem>
#include <Windows.h>
#include "AJ_Macro.h"

// Disable specific warnings temporarily
#pragma warning(push)
#pragma warning(disable : 4996) // Disable deprecated functions warning

namespace AJimpa
{

    class wTextFile
    {
    private:
        std::wofstream outFile;
        std::wstring filePath;

    public:
        /**
         * @brief Constructs a wTextFile for the specified file.
         *
         * @param filePath The path to the file to open.
         */
        wTextFile(const std::wstring &filePath)
        {
            try
            {
                this->filePath = filePath;
                outFile.open(filePath, std::ios::out | std::ios::app);
                if (!outFile.is_open())
                {
                    throw std::ios_base::failure("Failed to open file");
                }

                // Set the locale to handle Unicode
                outFile.imbue(std::locale(outFile.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
            }
            catch (const std::exception &e)
            {
                Debug(e.what(), AJDebugtype::System);
            }
        }

        /**
         * @brief Closes the file upon destruction of the wTextFile object.
         */
        ~wTextFile()
        {
            try
            {
                if (outFile.is_open())
                {
                    outFile.close();
                }
            }
            catch (const std::exception &e)
            {
                Debug(e.what(), AJDebugtype::System);
            }
        }

        /**
         * @brief Writes a line of text to the file.
         *
         * @param text The line of text to write.
         */
        void WriteLine(const std::wstring &text)
        {
            try
            {
                if (outFile.is_open())
                {
                    outFile << text << std::endl;
                    if (outFile.fail())
                    {
                        throw std::ios_base::failure("Failed to write to file");
                    }
                }
                else
                {
                    Debug("File is not open.", AJDebugtype::Error);
                }
            }
            catch (const std::exception &e)
            {
                Debug(e.what(), AJDebugtype::System);
            }
        }


        /**
         * @brief Flushes the output buffer to the file.
         */
        void Flush()
        {
            try
            {
                if (outFile.is_open())
                {
                    outFile.flush();
                    if (outFile.fail())
                    {
                        throw std::ios_base::failure("Failed to flush to file");
                    }
                }
            }
            catch (const std::exception &e)
            {
                Debug(e.what(), AJDebugtype::System);
            }
        }

        /**
         * @brief Checks if the file is empty.
         *
         * @return True if the file is empty, otherwise false.
         */
        bool IsEmpty()
        {
            if (outFile.good())
            {
                return outFile.tellp() == std::streampos(0);
            }
            throw std::ios_base::failure("Stream is not in a good state.");
        }

        /**
         * @brief Deletes the file.
         *
         * @return True if the file was deleted, otherwise false.
         */
        bool DeleteFile()
        {
            if (outFile.is_open())
            {
                outFile.close(); // Ensure the file is closed before deleting
            }
            // Check if the file exists and delete it
            if (std::filesystem::exists(filePath))
            {
                return std::filesystem::remove(filePath);
            }
            return false;
        }

        /**
         * @brief Converts a UTF-8 encoded string to a wide string.
         *
         * @param str The UTF-8 encoded string.
         * @return The converted wide string.
         */
        std::wstring Utf8ToWideString(const std::string &str)
        {
            if (str.empty())
                return std::wstring();

            int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
            std::wstring wstrTo(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
            return wstrTo;
        }
    };

}

// Re-enable the warnings that were disabled
#pragma warning(pop)