#include <iostream>
#include <queue>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

bool HasReadPermissions(const fs::path& path) {
    try {
        std::ifstream file(path);
        if (file.is_open()) {
            file.close();
            return true; // Successfully opened the file, so we have read permissions
        }
        return false; // Failed to open the file, likely due to lack of permissions
    } catch (...) {
        return false; // Exception occurred, likely due to lack of permissions
    }
}

void SearchFiles(const std::string& directory, const std::string& outputFile) {
    std::queue<fs::path> fileQueue;

    // Enqueue the initial directory
    fileQueue.push(directory);

    // Open the output file
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    try {
        // Process files in the queue
        while (!fileQueue.empty()) {
            // Get the next directory to search
            fs::path currentDir = fileQueue.front();
            fileQueue.pop();

            // Iterate through the contents of the directory
            for (const auto& entry : fs::directory_iterator(currentDir)) {
                if (HasReadPermissions(entry.path())) {
                    if (fs::is_directory(entry.path())) {
                        // If the entry is a directory, enqueue it for further search
                        fileQueue.push(entry.path());
                    } else if (fs::is_regular_file(entry.path())) {
                        // If the entry is a regular file, write its path to the output file
                        outFile << entry.path() << std::endl;
                    }
                } else {
                    std::cerr << "Access denied for: " << entry.path() << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    // Close the output file
    outFile.close();
}

int main() {
    std::string directoryToSearch = R"(D:\)";
    std::string outputFile = "output.txt";

    // Call the file search function
    SearchFiles(directoryToSearch, outputFile);

    std::cout << "File paths have been written to " << outputFile << std::endl;

    std::cin.get();
    return 0;
}

