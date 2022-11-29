#include <windows.h>
#include <winnt.h>
#include <TlHelp32.h>

#include <vector>
#include <string>
#include <iostream>

const char *PATH_TO_KILLER = R"(C:\Users\pimak\CLionProjects\Os-Labs\process_killer\killer\cmake-build-debug\killer.exe)";
const LPCTSTR PROCESSES = "Telegram.exe,Spotify.exe";
const CHAR* PROCESSES_NAME = "Discord.exe";
const CHAR* PROCESSES_ID_NAMES = "3856";
//change id according to taskhost
const LPCTSTR GLOBAL_VARIABLE_NAME = "PROC_TO_KILL";

bool ifProcessNameExist(std::string name);
bool ifProcessIdExist(int id);

void removeFromVariableTest();
void removeByIdTest();
void removeByNameTest();

int main(){
    removeFromVariableTest();
    removeByIdTest();
    removeByNameTest();
}


bool ifProcessNameExist(std::string name){
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    PROCESSENTRY32 procEntry;
    procEntry.dwSize = sizeof(procEntry);
    BOOL isMoreProcesses = Process32First(snapshot, &procEntry);

    while (isMoreProcesses){
        if (name == procEntry.szExeFile){
            return true;
        }
        isMoreProcesses = Process32Next(snapshot, &procEntry);
    }
    return false;
}

void removeFromVariableTest(){
    if (SetEnvironmentVariable(GLOBAL_VARIABLE_NAME ,PROCESSES)){

        std::cout << "Spotify.exe: " << ifProcessNameExist("Spotify.exe") << " ";
        std::cout << "Telegram.exe: " << ifProcessNameExist("Telegram.exe") << std::endl;

        STARTUPINFO si = {sizeof(si)};
        PROCESS_INFORMATION process_information;
        const int BUFF_SIZE = 500;
        char buffer[BUFF_SIZE];
        strcpy_s(buffer, 500, PATH_TO_KILLER);

        CreateProcess(nullptr, buffer, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &process_information);

        WaitForSingleObject(process_information.hProcess, INFINITE);
        WaitForSingleObject(process_information.hThread, INFINITE);
        CloseHandle(process_information.hThread);
        CloseHandle(process_information.hProcess);

        Sleep(500);

        std::cout << "Spotify.exe: " << ifProcessNameExist("Spotify.exe") << " ";
        std::cout << "Telegram.exe: " << ifProcessNameExist("Telegram.exe") << std::endl;
    }
    SetEnvironmentVariable(GLOBAL_VARIABLE_NAME, nullptr);
}

void removeByIdTest(){

    std::cout << PROCESSES_ID_NAMES << " " << ifProcessIdExist(atoi(PROCESSES_ID_NAMES)) << std::endl;

    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION process_information;
    const int BUFF_SIZE = 500;
    char buffer[BUFF_SIZE];
    strcpy_s(buffer, 500, PATH_TO_KILLER);
    strcat_s(buffer, " --id ");
    strcat_s(buffer, PROCESSES_ID_NAMES);

    CreateProcess(nullptr, buffer, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &process_information);

    Sleep(500);

    std::cout << PROCESSES_ID_NAMES << " " << ifProcessIdExist(atoi(PROCESSES_ID_NAMES)) << std::endl;
}

bool ifProcessIdExist(int id){
    HANDLE handle = OpenProcess(PROCESS_TERMINATE, FALSE, id);
    return handle != nullptr;

}

void removeByNameTest(){

    std::cout << PROCESSES_NAME << " " << ifProcessNameExist(PROCESSES_NAME) << std::endl;

    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION process_information;
    const int BUFF_SIZE = 500;
    char buffer[BUFF_SIZE];
    strcpy_s(buffer, 500, PATH_TO_KILLER);
    strcat_s(buffer, " --name ");
    strcat_s(buffer, PROCESSES_NAME);

    CreateProcess(nullptr, buffer, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &process_information);

    Sleep(500);

    std::cout << PROCESSES_NAME << " " << ifProcessNameExist(PROCESSES_NAME) << std::endl;
}