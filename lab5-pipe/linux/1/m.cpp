#include <string>
#include <vector>
#include <iostream>

std::vector<int> parseLine(std::string line){
    std::string word;
    auto words = std::vector<int>();

    for (char i : line) {
        if (i == '\n'){
            break;
        }
        if  (i != ' ') {
            word.push_back(i);
        }
        else{
            if (word.empty()){
                continue;
            }
            words.push_back(stoi(word));
            word.clear();
        }
    }

    words.push_back(stoi(word));
    return words;
}

int main(){
    std::string line;
    std::getline(std::cin, line);

    auto numbers = parseLine(line);

    for (int item : numbers){
        std::cout << item * 7 << " ";
    }
    std::cout << std::endl;
    return 0;
}