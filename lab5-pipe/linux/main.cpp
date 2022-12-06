
#include <string>
#include <sys/wait.h>

std::string processMPath = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/1/cmake-build-debug/M";
std::string processAPath = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/2/cmake-build-debug/A";
std::string processPPath = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/3/cmake-build-debug/P";
std::string processSPath = "/home/skalem/CLionProjects/Os-Labs/lab5-pipe/linux/4/cmake-build-debug/S";

int main(int argc, char* argv[]){
    int pipefd[2];
    pipe(pipefd);

    if (fork() == 0){
        dup2(pipefd[0], STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execl(processMPath.c_str(), "");
        exit(0);
    }
    else {
        //wait(nullptr);
        if (fork() == 0){
            dup2(pipefd[0], STDIN_FILENO);
            dup2(pipefd[1], STDOUT_FILENO);

            close(pipefd[0]);
            close(pipefd[1]);

            execl(processAPath.c_str(), "");
            exit(0);
        }
        else {
            //wait(nullptr);
            if (fork() == 0){
                dup2(pipefd[0], STDIN_FILENO);
                dup2(pipefd[1], STDOUT_FILENO);

                close(pipefd[0]);
                close(pipefd[1]);

                execl(processPPath.c_str(), "");
                exit(0);
            }
            else{
                //wait(nullptr);
                if (fork() == 0){
                    dup2(pipefd[0], STDIN_FILENO);
                    dup2(pipefd[1], STDOUT_FILENO);

                    close(pipefd[0]);
                    close(pipefd[1]);

                    execl(processSPath.c_str(), "");
                    exit(0);
                }
                else {
                    //wait(nullptr);
                    close(pipefd[0]);
                    close(pipefd[1]);
                }
            }
        }
    }
}