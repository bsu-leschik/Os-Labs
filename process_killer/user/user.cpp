#include <windows.h>
#include <cstdlib>
#include <winnt.h>
#include <TlHelp32.h>

#include <vector>
#include <string>
#include <iostream>

const CHAR* PATH_TO_KILLER = "../../killer/cmake-build-debug/killer.exe";
const CHAR* PROCESSES = "Telegram.exe";
const CHAR* PROCESSES_NAME = "Discord.exe";
const CHAR* PROCESSES_ID_NAMES = "Chrome.exe";
const CHAR* GLOBAL_VARIABLE_NAME = "PROC_TO_KILL";

bool ifProcessNameExist(std::string name);
bool ifProcessIdExist(int id);


int main(){
    if (SetEnvironmentVariable(GLOBAL_VARIABLE_NAME ,PROCESSES)){
        std::cout << "Spotify.exe: " << ifProcessNameExist("Spotify.exe");
        std::cout << "Telegram.exe: " << ifProcessNameExist("Telegram.exe");

        STARTUPINFO si = {sizeof(si)};
        PROCESS_INFORMATION process_information;
        const int BUFF_SIZE = 500;
        char buff[BUFF_SIZE];
        strcpy_s(buff, BUFF_SIZE, PATH_TO_KILLER);

        CreateProcess(nullptr, buff, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &process_information);
        WaitForSingleObject(process_information.hThread, INFINITE);
        CloseHandle(process_information.hThread);
        WaitForSingleObject(process_information.hProcess, INFINITE);
        CloseHandle(process_information.hProcess);

        std::cout << "Spotify.exe: " << ifProcessNameExist("Spotify.exe");
        std::cout << "Telegram.exe: " << ifProcessNameExist("Telegram.exe");
    }

    //SetEnvironmentVariable(GLOBAL_VARIABLE_NAME, NULL);
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

bool ifProcessIdExist(int id){
    HANDLE handle = OpenProcess(PROCESS_TERMINATE, FALSE, id);
    return handle != nullptr;

}
