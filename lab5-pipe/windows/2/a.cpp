#include <string>
#include <vector>
#include <iostream>
#include <sstream>

int main(){
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    int item;
    ss >> item;
    while (!ss.fail()){
        std::cout << 13 + item << " ";
        ss >> item;
    }
    std::cout << std::endl;
}