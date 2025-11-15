#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "AJ_Macro.h"

namespace AJimpa
{

    class TextFile
    {
    private:
        std::ofstream outFile;

    public:
        /**
         * @brief Constructs a StreamWriter for the specified file.
         *
         * @param filePath The path to the file to open.
         */
        TextFile(const std::string &filePath)
        {
            try
            {
                outFile.open(filePath, std::ios::out | std::ios::app);
                if (!outFile.is_open())
                {
                    throw std::ios_base::failure("Failed to open file");
                }
            }
            catch (const std::exception &e)
            {
                Debug(e.what(), AJDebugtype::System);
            }
        }

        /**
         * @brief Closes the file upon destruction of the StreamWriter object.
         */
        ~TextFile()
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
        void WriteLine(const std::string &text)
        {
            try
            {
                if (outFile.is_open())
                {
                    outFile << text << std::endl;
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
                }
            }
            catch (const std::exception &e)
            {
                Debug(e.what(), AJDebugtype::System);
            }
        }
    };

}
