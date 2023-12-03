#include <string>
#include <sstream>
#include <iostream>


int main(){
    std::string line;
    std::getline(std::cin, line);

    int sum = 0;
    std::stringstream ss(line);
    int item;
    ss >> item;
    while (!ss.eof()){
        sum += item;
        ss >> item;
    }
    std::cout << sum << std::endl;
}