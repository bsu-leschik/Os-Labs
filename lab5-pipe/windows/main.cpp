#include <windows.h>

#include <namedpipeapi.h>
#include <fileapi.h>

#include <string>

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

int main(){
    HANDLE descriptors[2];

    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.dwFlags = STARTF_USESTDHANDLES;

    for (int i = 0; i < 3; ++i) {
        openPipe(descriptors);
        PROCESS_INFORMATION process_information;

        ZeroMemory( &process_information, sizeof(process_information) );

        si.hStdOutput = descriptors[1];

        CreateProcess(nullptr, processes[i].data(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si,
                      &process_information);

        CloseHandle(descriptors[1]);
        WaitForSingleObject(process_information.hProcess, INFINITE);
        WaitForSingleObject(process_information.hThread, INFINITE);
        CloseHandle(process_information.hThread);
        CloseHandle(process_information.hProcess);
        si.hStdInput = descriptors[0];
    }

    PROCESS_INFORMATION process_information;
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CreateProcess(nullptr, processes[3].data(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si,
                  &process_information);
    WaitForSingleObject(process_information.hProcess, INFINITE);
    WaitForSingleObject(process_information.hThread, INFINITE);
    CloseHandle(process_information.hThread);
    CloseHandle(process_information.hProcess);

    return 0;
}