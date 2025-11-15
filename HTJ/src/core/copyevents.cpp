
#pragma comment(lib, "Advapi32.lib")


#include <Windows.h>
#include <iostream>
#include <string>

// Function to display error message and exit
void displayError(const std::string& errorMessage) {
    std::cerr << "Error: " << errorMessage << " (Error code: " << GetLastError() << ")" << std::endl;
    exit(EXIT_FAILURE);
}

// Function to read and display events from the Windows System event log related to file copying
void readFileCopyingEvents() {
    HANDLE hEventLog = OpenEventLog(nullptr, "System");
    if (hEventLog == nullptr) {
        displayError("Failed to open event log");
    }

    DWORD dwBytesRead;
    BYTE buffer[4096];
    DWORD dwRead;

    while (ReadEventLog(hEventLog, EVENTLOG_BACKWARDS_READ | EVENTLOG_SEQUENTIAL_READ, 0, buffer, sizeof(buffer), &dwBytesRead, &dwRead)) {
        EVENTLOGRECORD* pEvent = (EVENTLOGRECORD*)buffer;
        while ((BYTE*)pEvent < buffer + dwBytesRead) {
            char* message = (char*)((BYTE*)pEvent + pEvent->StringOffset);
            if (strstr(message, "copy")) {
                std::cout << "Event ID: " << pEvent->EventID << std::endl;
                //std::cout << "Time: " << std::ctime((time_t*)&pEvent->TimeGenerated);
                std::cout << "Type: " << (pEvent->EventType == EVENTLOG_ERROR_TYPE ? "Error" :
                                            (pEvent->EventType == EVENTLOG_WARNING_TYPE ? "Warning" :
                                                (pEvent->EventType == EVENTLOG_INFORMATION_TYPE ? "Information" : "Unknown"))) << std::endl;
                std::cout << "Source: " << message << std::endl;
                std::cout << std::endl;
            }
            pEvent = (EVENTLOGRECORD*)((BYTE*)pEvent + pEvent->Length);
        }
    }
    CloseEventLog(hEventLog);
}

int main() {
    readFileCopyingEvents();
    std::cin.get();
}
