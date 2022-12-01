#include <string>
#include <unistd.h>
#include <vector>

std::vector<int> parseLine(std::string line){
    std::string word;
    auto words = std::vector<int>();

    for (char i : line) {
        if  (i != ' ') {
            word.push_back(i);
        }
        else{
            words.push_back(stoi(word));
            word.clear();
        }
    }

    words.push_back(stoi(word));
    return words;
}

int main(int argc, char *argv[]){
    if (argc < 2){
        return 1;
    }

    int pipefd[] = {atoi(argv[0]), atoi(argv[1])};
    char* buffer;
    read(pipefd[0], buffer, 500);

    auto numbers = parseLine(std::string(buffer));
    delete buffer;

    char* out[2];
    int sum;
    for (int i = 0; i < numbers.size(); ++i) {
        sum += numbers[i];
    }

    out[0] = std::to_string(sum).data();
    out[1] = new char('\n');

    write(pipefd[1], out, numbers.size());
    return 0;
}