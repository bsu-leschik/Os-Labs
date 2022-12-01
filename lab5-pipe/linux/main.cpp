
#include <string>
#include <charconv>
#include <iostream>
#include <sys/wait.h>

std::string processMPath = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/1/cmake-build-debug/M";
std::string processAPath = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/2/cmake-build-debug/A";
std::string processPPath = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/3/cmake-build-debug/P";
std::string processSPath = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/4/cmake-build-debug/S";

int main(int argc, char* argv[]){
    int pipefd[2];

    pipe(pipefd);

    std::string readPipe = std::to_string(pipefd[0]);
    std::string writePipe = std::to_string(pipefd[1]);

    char* pipefdChar[] = {readPipe.data(), writePipe.data()};

    if (fork() == 0){
        execv(processMPath.c_str(), pipefdChar);
        close(pipefd[0]);
        close(pipefd[1]);
        exit(0);
    }
    else {
        write(pipefd[1], argv[1], argc);
        close(pipefd[1]);
        wait(nullptr);
        if (fork() == 0){
            execv(processAPath.c_str(), pipefdChar);
            //char* buffer1;
            //read(pipefd[0], buffer1, argc);
            close(pipefd[0]);
            close(pipefd[1]);
            exit(0);
        }
        else {
            wait(nullptr);
            if (fork() == 0){
                execv(processPPath.c_str(), pipefdChar);
                close(pipefd[0]);
                close(pipefd[1]);
                exit(0);
            }
            else{
                wait(nullptr);
                if (fork() == 0){
                    execv(processSPath.c_str(), pipefdChar);
                    close(pipefd[0]);
                    close(pipefd[1]);
                    exit(0);
                }
                else {
                    wait(nullptr);
                }
                char *buffer;
                read(pipefd[0], buffer, 500);
                close(pipefd[0]);
                std::cout << "answer: " << atoi(buffer);
            }
        }
    }
}