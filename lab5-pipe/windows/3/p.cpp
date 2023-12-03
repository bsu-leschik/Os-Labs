#include <string>
#include <sstream>
#include <iostream>

int main(){
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    int item;
    ss >> item;
    while (!ss.fail()){
        std::cout << item * item * item << " ";
        ss >> item;
    }
    std::cout << std::endl;
}