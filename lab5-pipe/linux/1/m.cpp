#include <string>
#include <iostream>
#include <sstream>

int main(){
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    int k;
    ss >> k;
    while (!ss.fail()){
        std::cout << k * 7 << " ";
        ss >> k;
    }
    std::cout << std::endl;
    return 0;
}