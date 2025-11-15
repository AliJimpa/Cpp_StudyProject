#include <windows.h>
#include <winhttp.h>
#include <iostream>
#include <string>

#pragma comment(lib, "winhttp.lib")

int main()
{
    std::string address;
    // Taking input from user and store it in variable
    std::cin >> address;
    // Output the entered age
    std::cout << "Webside address entered: " << address;

    HINTERNET hSession = WinHttpOpen(L"C++ Console App/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession)
    {
        std::cerr << "Failed to open session\n";
        return 1;
    }

    HINTERNET hConnect = WinHttpConnect(hSession,address,
                                        INTERNET_DEFAULT_HTTP_PORT, 0);
    if (!hConnect)
    {
        std::cerr << "Failed to connect\n";
        WinHttpCloseHandle(hSession);
        return 1;
    }

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/",
                                            nullptr, WINHTTP_NO_REFERER,
                                            WINHTTP_DEFAULT_ACCEPT_TYPES,
                                            0);
    if (!hRequest)
    {
        std::cerr << "Failed to open request\n";
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    if (!WinHttpSendRequest(hRequest,
                            WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                            WINHTTP_NO_REQUEST_DATA, 0,
                            0, 0) ||
        !WinHttpReceiveResponse(hRequest, nullptr))
    {
        std::cerr << "Request failed\n";
    }
    else
    {
        DWORD bytesAvailable = 0;
        while (WinHttpQueryDataAvailable(hRequest, &bytesAvailable) && bytesAvailable > 0)
        {
            char *buffer = new char[bytesAvailable + 1];
            DWORD bytesRead = 0;
            if (WinHttpReadData(hRequest, buffer, bytesAvailable, &bytesRead))
            {
                buffer[bytesRead] = '\0';
                std::cout << buffer;
            }
            delete[] buffer;
        }
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    return 0;
}
