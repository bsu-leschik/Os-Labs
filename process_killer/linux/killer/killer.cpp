#include <cstdlib>

#include <string>
#include <vector>
#include <cstring>

#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>

void killProcessByName(char* name);
void killProcessByID(int id);
void killProcessesFromVariable();

std::string NAME_PARAMETER = "--name";
std::string ID_PARAMETER = "--id";
std::string GLOBAL_VARIABLE_NAME = "PROC_TO_KILL";

int main(int argc, char *argv[]){
    for (int i = 0; i < argc; ++i) {
        if  (strcmp(argv[i], NAME_PARAMETER.c_str()) == 0){
            killProcessByName(argv[++i]);
            break;
        }
        else if(strcmp(argv[i], ID_PARAMETER.c_str()) == 0){
            killProcessByID(atoi(argv[++i]));
            break;
        }
    }
    killProcessesFromVariable();

    return 0;
}

std::vector<std::string> getWords(const std::string& line){
    std::string word;
    std::vector<std::string> words = std::vector<std::string>();

    for (char i : line) {
        if  (i != ',') {
            word.push_back(i);
        }
        else{
            words.push_back(word);
            word.clear();
        }
    }

    words.push_back(word);
    return words;
}

void killProcessesFromVariable(){
    char* processesToKill = getenv(GLOBAL_VARIABLE_NAME.c_str());
    if (processesToKill == nullptr){
        return;
    }
    auto namesPrToKill = getWords(processesToKill);

    for (auto item: namesPrToKill){
        killProcessByName(item.data());
    }
}


void killProcessByName(char *name){
    char* command = new char[200];
    strcat(command, "pidof ");
    strcat(command, name);

    FILE* pipe = popen(command, "r");

    char buf[512];
    fgets(buf, 512, pipe);

    if(!isdigit(buf[0])){
        return;
    }
    int pid = strtoul(buf, NULL, 10);
    killProcessByID(pid);
}

void killProcessByID(int id){
    kill(id, SIGTERM);
}