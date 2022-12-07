
#include <string>
#include <sys/wait.h>
#include <iostream>

std::string processes[] = {"/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/1/cmake-build-debug/M",
 "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/2/cmake-build-debug/A",
 "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/3/cmake-build-debug/P",
 "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/4/cmake-build-debug/S"};

int main(){

    int pipefd[2];

    for (int i = 0; i < 3; ++i) {
        pipe(pipefd);

        if(fork() == 0){
            dup2(pipefd[1], STDOUT_FILENO);

            execl(processes[i].c_str(), "");
            std::exit(0);
        }
        else{
            close(pipefd[1]);
            wait(nullptr);
            dup2(pipefd[0], STDIN_FILENO);
        }
    }

    if (fork() == 0) {
        execl(processes[3].c_str(), "");
        exit(0);
    }
    wait(nullptr);
}