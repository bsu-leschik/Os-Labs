#include <windows.h>

#include <cstdlib>
#include <winnt.h>
#include <TlHelp32.h>
#include <string>
#include <vector>


void killProcessByName(char* name);
void killProcessByID(DWORD id);
void killProcessesFromVariable();

const char* NAME_PARAMETER = "--name";
const char* ID_PARAMETER = "--id";
const CHAR* GLOBAL_VARIABLE_NAME = "PROC_TO_KILL";
const int VAR_LENGTH = 200;

int main(int argc, char *argv[]){
    for (int i = 0; i < argc; ++i) {
        if  (argv[i] == NAME_PARAMETER){
            killProcessByName(argv[++i]);
        }
        else if(argv[i] == ID_PARAMETER){
            killProcessByID(atoi(argv[++i]));
        }
    }
    killProcessesFromVariable();
}

std::vector<std::string> getWords(CHAR* line,DWORD length){
    std::string word;
    std::vector<std::string> words;

    for (DWORD i = 0; i < length - 1; ++i) {
        if  (line[i] != ',') {
            word.push_back(line[i]);
        }
        else{
            words.push_back(word);
            word.clear();
        }
    }

    return words;
}

void killProcessesFromVariable(){
    CHAR *processesToKill = new CHAR[200];
    DWORD length =  GetEnvironmentVariableA(GLOBAL_VARIABLE_NAME, processesToKill, VAR_LENGTH);
    auto namesPrToKill = getWords(processesToKill, length);

    for (auto item: namesPrToKill){
        killProcessByName(item.data());
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