#include <windows.h>
#include <namedpipeapi.h>
#include <fileapi.h>

#include <string>
#include <iostream>

std::string processes[] = { R"(C:\Users\pimak\CLionProjects\Os-Labs\lab5-pipe\windows\1\cmake-build-debug\M.exe)",
                            R"(C:\Users\pimak\CLionProjects\Os-Labs\lab5-pipe\windows\2\cmake-build-debug\A.exe)",
                            R"(C:\Users\pimak\CLionProjects\Os-Labs\lab5-pipe\windows\3\cmake-build-debug\P.exe)",
                            R"(C:\Users\pimak\CLionProjects\Os-Labs\lab5-pipe\windows\4\cmake-build-debug\S.exe)"};

std::string currentDir;

SECURITY_ATTRIBUTES securityAttributes = {
        sizeof(securityAttributes),
        NULL,
        TRUE
};

STARTUPINFO si = {sizeof(si)};


void openPipe(HANDLE descriptors[2]){
    CreatePipe(&descriptors[0], &descriptors[1], &securityAttributes, 0);
}

void closePipe(HANDLE descriptors[2]){
    CloseHandle(descriptors[0]);
    CloseHandle(descriptors[1]);
}

void configureStartupInfo(HANDLE descriptors[2]){
    si.hStdInput = descriptors[0];
    //si.hStdOutput = descriptors[1];
    //si.hStdError = descriptors[1];
    si.dwFlags = STARTF_USESTDHANDLES;
}

int main(){
    HANDLE descriptors[2];

    for (int i = 0; i < 3; ++i) {
        openPipe(descriptors);
        PROCESS_INFORMATION process_information;
        configureStartupInfo(descriptors);
        CreateProcess(nullptr, processes[0].data(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si,
                      &process_information);
        closePipe(descriptors);
        WaitForSingleObject(process_information.hProcess, INFINITE);
        WaitForSingleObject(process_information.hThread, INFINITE);
        CloseHandle(process_information.hThread);
        CloseHandle(process_information.hProcess);
    }

    return 0;
}