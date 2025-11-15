#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip> // Include <iomanip> for std::put_time
#include <ctime>   // Include <ctime> for localtime_s
#include "JimpaLibrary.h"

namespace fs = std::filesystem;

// Function to retrieve creation date of a file
std::time_t getFileCreationTime(const fs::path& filePath) {
    std::error_code ec;
    auto timePoint = fs::last_write_time(filePath, ec);
    if (ec) {
        std::cerr << "Error: Unable to retrieve file creation time." << std::endl;
        return -1; // Return invalid time
    }
    auto duration = timePoint.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::system_clock::duration>(duration).count(); // Convert file_time_type to time_t
}

// Function to retrieve the date of the last copy operation of a file
std::time_t getLastCopyDate(const fs::path& filePath) {
    // You need to implement the logic for tracking the last copy date
    // This might involve parsing a log file or maintaining metadata in a separate file
    // For simplicity, let's return the creation date as the last copy date in this example
    return getFileCreationTime(filePath);
}

int main() {
    fs::path filePath;
     Request("WritePath",filePath);

    // Get file creation time
    std::time_t creationTime = getFileCreationTime(filePath);
    LOG(creationTime);
    if (creationTime != -1) {
        std::tm creationTimeInfo;
        if (localtime_s(&creationTimeInfo, &creationTime) == 0) { // Use localtime_s to convert creation time to local time
            // Convert creation time info to a local time string
            std::cout << "File Creation Date: " << std::put_time(&creationTimeInfo, "%c") << std::endl;

            // Get date of the last copy operation
            std::time_t lastCopyDate = getLastCopyDate(filePath);
            if (lastCopyDate != -1) {
                std::tm lastCopyTimeInfo;
                if (localtime_s(&lastCopyTimeInfo, &lastCopyDate) == 0) { // Use localtime_s to convert last copy date to local time
                    // Convert last copy time info to a local time string
                    std::cout << "Last Copy Date: " << std::put_time(&lastCopyTimeInfo, "%c") << std::endl;
                } else {
                    std::cerr << "Error: Unable to format last copy time." << std::endl;
                }
            } else {
                std::cerr << "Error: Unable to retrieve last copy date." << std::endl;
            }
        } else {
            std::cerr << "Error: Unable to format creation time." << std::endl;
        }
    } else {
        std::cerr << "Error: Unable to retrieve file creation time." << std::endl;
    }

    return 0;
}
