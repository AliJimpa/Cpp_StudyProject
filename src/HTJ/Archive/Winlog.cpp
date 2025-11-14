
#pragma comment(lib, "Advapi32.lib")

#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip> // for std::put_time
#include <ctime>   // for localtime_s
#include "JimpaLibrary.h"

// Function to display error message and exit
void displayError(const std::string& errorMessage) {
    std::cerr << "Error: " << errorMessage << " (Error code: " << GetLastError() << ")" << std::endl;
    exit(EXIT_FAILURE);
}

// Function to read and display event logs related to file copying
void readEventLogs() {
    HANDLE hEventLog = OpenEventLog(nullptr, "Security");
    if (hEventLog == nullptr) {
        displayError("Failed to open event log");
    }

    DWORD dwBytesRead;
    BYTE buffer[4096];
    DWORD dwRead;

    while (ReadEventLog(hEventLog, EVENTLOG_BACKWARDS_READ | EVENTLOG_SEQUENTIAL_READ, 0, buffer, sizeof(buffer), &dwBytesRead, &dwRead)) {
        EVENTLOGRECORD* pEvent = (EVENTLOGRECORD*)buffer;
        while ((BYTE*)pEvent < buffer + dwBytesRead) {
            if (pEvent->EventType == EVENTLOG_AUDIT_SUCCESS || pEvent->EventType == EVENTLOG_AUDIT_FAILURE) {
                // Check if the event is related to file copying
                char* message = (char*)((BYTE*)pEvent + sizeof(EVENTLOGRECORD));
                if (strstr(message, "copy")) {
                    std::tm timeInfo;
                    if (localtime_s(&timeInfo, (time_t*)&pEvent->TimeGenerated) == 0) {
                        char timeBuffer[26];
                        if (std::strftime(timeBuffer, sizeof(timeBuffer), "%c", &timeInfo)) {
                            std::cout << "Event ID: " << pEvent->EventID << std::endl;
                            std::cout << "Time: " << timeBuffer << std::endl;
                            std::cout << "Message: " << message << std::endl;
                            std::cout << std::endl;
                        } else {
                            std::cerr << "Error: Unable to format time." << std::endl;
                        }
                    } else {
                        std::cerr << "Error: Unable to get local time." << std::endl;
                    }
                }
            }
            pEvent = (EVENTLOGRECORD*)((BYTE*)pEvent + pEvent->Length);
        }
    }
    CloseEventLog(hEventLog);
}

int main() {
    LOG("AppStarter");
    readEventLogs();
    std::cin.get();
}
