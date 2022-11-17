#include <cstdlib>
#include <winnt.h>
#include <windows.h>
#include <TlHelp32.h>


void killProcessByName(char* name);
void killProcessByID(DWORD id);

const char* NAME_PARAMETER = "--name";
const char* ID_PARAMETER = "--id";

int main(int argc, char *argv[]){
    for (int i = 0; i < argc; ++i) {
        if  (argv[i] == NAME_PARAMETER){
            killProcessByName(argv[++i]);
        }
        else if(argv[i] == ID_PARAMETER){
            killProcessByID(atoi(argv[++i]));
        }
    }
}

void killProcessByName(char *name){
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    PROCESSENTRY32 procEntry;
    procEntry.dwSize = sizeof(procEntry);
    BOOL isMoreProcesses = Process32First(snapshot, &procEntry);

    while (isMoreProcesses){
        if (name == procEntry.szExeFile){
            killProcessByID(procEntry.th32ProcessID);
        }
        isMoreProcesses = Process32Next(snapshot, &procEntry);
    }
}

void killProcessByID(DWORD id){
    HANDLE handle = OpenProcess(PROCESS_TERMINATE, FALSE, id);
    if (handle != nullptr) {
        TerminateProcess(handle, 2);
    }
    CloseHandle(handle);
}