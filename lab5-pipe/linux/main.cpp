#include <string>
#include <sys/wait.h>
#include <iostream>

std::string home = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/cmake-build-debug/";

std::string processes[] = {home + "M",home + "A",home + "P",home + "S"};

int main(){

    int pipefd[2];

    for (int i = 0; i < 3; ++i) {

        pipe(pipefd);

        if(fork() == 0){
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            execl(processes[i].c_str(), "", nullptr);
            exit(0);
        }
        else {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            wait(nullptr);
        }
    }

    if (fork() == 0) {
        execl(processes[3].c_str(), "", nullptr);
        exit(0);
    }
    wait(nullptr);
}