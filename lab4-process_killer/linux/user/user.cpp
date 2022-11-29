#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

std::string PATH_TO_KILLER = "/home/skalem/CLionProjects/Os-Labs/lab4-process_killer/linux/killer/cmake-build-debug/killer";
std::string PROCESSES = "telegram-desktop spotify";
std::string PROCESSES_NAME = "Discord";
std::string PROCESSES_ID_NAMES = "10480";
//change id according to taskhost
std::string GLOBAL_VARIABLE_NAME = "PROC_TO_KILL";
std::string NAME_STRING = "--name";
std::string ID_STRING = "--id";

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

    std::string buffer;
    char* buf = new char[512];
    fgets(buf, 512, pipe);

    bool isPid = std::isdigit(buf[0]);
    delete[] buf;
    return isPid;
}

void removeFromVariableTest(){
    if (!setenv(GLOBAL_VARIABLE_NAME.c_str(), PROCESSES.c_str(), 1)){

        std::cout << "spotify: " << ifProcessNameExist("spotify") << " ";
        std::cout << "telegram-desktop: " << ifProcessNameExist("telegram-desktop") << std::endl;

        int childPid = fork();

        if (childPid == 0){
            std::cout << execl(PATH_TO_KILLER.c_str(), NULL) << std::endl;
            exit(0);
        }
        else {
            waitpid(childPid, NULL, 0);
            std::cout << "spotify: " << ifProcessNameExist("spotify") << " ";
            std::cout << "telegram-desktop: " << ifProcessNameExist("telegram-desktop") << std::endl;
        }
    }
    unsetenv(GLOBAL_VARIABLE_NAME.c_str());
}

void removeByIdTest(){

    std::cout << PROCESSES_ID_NAMES << " " << ifProcessIdExist(stoi(PROCESSES_ID_NAMES)) << std::endl;

    int childPid = fork();

    if (childPid == 0){
        char** args = new char * [2];
        args[0] = ID_STRING.data();
        args[1] = PROCESSES_ID_NAMES.data();
        execv(PATH_TO_KILLER.c_str(), args);
        exit(0);
    }
    else {
        waitpid(childPid, NULL, 0);
        std::cout << PROCESSES_ID_NAMES << " " << ifProcessIdExist(stoi(PROCESSES_ID_NAMES)) << std::endl;
    }
}

bool ifProcessIdExist(int id){
    if (kill(id, 0) == 0){
        return true;
    }
    else {
        return false;
    }
}

void removeByNameTest(){

    std::cout << PROCESSES_NAME << " " << ifProcessNameExist(PROCESSES_NAME) << std::endl;

    if (fork() == 0){
        char** args = new char * [2];
        args[0] = NAME_STRING.data();
        args[1] = PROCESSES_NAME.data();
        execv(PATH_TO_KILLER.c_str(), args);
        exit(0);
    }
    else {
        wait(NULL);
        std::cout << PROCESSES_NAME << " " << ifProcessNameExist(PROCESSES_NAME) << std::endl;
    }
}