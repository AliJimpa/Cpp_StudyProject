#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime> // Include <ctime> for std::ctime_s
#include <thread>
#include "JimpaLibrary.h"

namespace fs = std::filesystem;

void logEvent(const std::string& message) {
    std::ofstream logfile("folder_log.txt", std::ios::app);
    if (logfile.is_open()) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        struct tm timeInfo;
        if (_localtime64_s(&timeInfo, &now) == 0) { // Use _localtime64_s to get local time
            char timeStr[26]; // Buffer to hold the formatted time string
            if (strftime(timeStr, sizeof(timeStr), "%c", &timeInfo) > 0) { // Use strftime to format the time
                logfile << timeStr << ": " << message << std::endl;
            } else {
                std::cerr << "Error: Unable to format time." << std::endl;
            }
        } else {
            std::cerr << "Error: Unable to get local time." << std::endl;
        }
    } else {
        std::cerr << "Error: Unable to open log file for writing." << std::endl;
    }
}

void monitorFolder(const fs::path &folder)
{
    for (const auto &entry : fs::directory_iterator(folder))
    {
        // Check if entry is a regular file
        if (entry.is_regular_file())
        {
            // Assuming copying is indicated by a file's last write time being updated
            auto lastWriteTime = fs::last_write_time(entry);
            // Log event if last write time has changed (indicating a copy event)
            // Note: This simple approach may not cover all copy events depending on usage
            if (lastWriteTime != entry.last_write_time())
            {
                logEvent("File " + entry.path().string() + " was copied.");
            }
        }
    }
}

int main()
{

    fs::path folderToMonitor;
    Request("WritePath", folderToMonitor);


    logEvent("Starting monitoring of folder: " + folderToMonitor.string());

    // Monitor the folder indefinitely
    while (true)
    {
        monitorFolder(folderToMonitor);
        // Sleep for some time before checking again (adjust as needed)
        std::this_thread::sleep_for(std::chrono::seconds(60)); // Check every minute
    }
    std::cin.get();
}
