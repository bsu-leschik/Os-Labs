#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

std::string PATH_TO_KILLER = "/home/skalem/CLionProjects/Os-Labs/process_killer/linux/killer/cmake-build-debug/killer";
std::string PROCESSES = "telegram-desktop, spotify";
std::string PROCESSES_NAME = "discord";
std::string PROCESSES_ID_NAMES = "18492";
//change id according to taskhost
std::string GLOBAL_VARIABLE_NAME = "PROC_TO_KILL";

bool ifProcessNameExist(const std::string& name);
bool ifProcessIdExist(int id);

void removeFromVariableTest();
void removeByIdTest();
void removeByNameTest();

int main(){
    removeFromVariableTest();
    removeByIdTest();
    removeByNameTest();
}


bool ifProcessNameExist(const std::string& name){
    char* command = new char[200];
    strcat(command, "pidof ");
    strcat(command, name.c_str());

    FILE* pipe = popen(command, "r");

    char buf[512];
    fgets(buf, 512, pipe);

    return isdigit(buf[0]);
}

void removeFromVariableTest(){
    if (setenv(GLOBAL_VARIABLE_NAME.c_str(), PROCESSES.c_str(), 1)){

        std::cout << "spotify: " << ifProcessNameExist("spotify") << " ";
        std::cout << "telegram-desktop: " << ifProcessNameExist("telegram-desktop") << std::endl;

        int child = fork();

        if (child == getpid()){
            execle(PATH_TO_KILLER.c_str(), PATH_TO_KILLER.c_str(), GLOBAL_VARIABLE_NAME.data());
            exit(0);
        }

        int stat;
        wait(&stat);

        std::cout << "spotify: " << ifProcessNameExist("spotify") << " ";
        std::cout << "telegram-desktop: " << ifProcessNameExist("telegram-desktop") << std::endl;
    }
    unsetenv(GLOBAL_VARIABLE_NAME.c_str());
}

void removeByIdTest(){

    std::cout << PROCESSES_ID_NAMES << " " << ifProcessIdExist(stoi(PROCESSES_ID_NAMES)) << std::endl;

    int child = fork();

    if (child == getpid()){
        std::string args = PATH_TO_KILLER;
        args.append(" ");
        args.append("--id ");
        args.append(PROCESSES_ID_NAMES);
        execl(PATH_TO_KILLER.c_str(), args.c_str());
        exit(0);
    }

    int stat;
    wait(&stat);

    std::cout << PROCESSES_ID_NAMES << " " << ifProcessIdExist(stoi(PROCESSES_ID_NAMES)) << std::endl;
}

bool ifProcessIdExist(int id){
    return kill(id, 0);

}

void removeByNameTest(){

    std::cout << PROCESSES_NAME << " " << ifProcessNameExist(PROCESSES_NAME) << std::endl;

    int child = fork();

    if (child == getpid()){
        std::string args = PATH_TO_KILLER;
        args.append(" ");
        args.append("--name ");
        args.append(PROCESSES_NAME);
        execl(PATH_TO_KILLER.c_str(), args.c_str());
        exit(0);
    }

    int stat;
    wait(&stat);

    std::cout << PROCESSES_NAME << " " << ifProcessNameExist(PROCESSES_NAME) << std::endl;
}