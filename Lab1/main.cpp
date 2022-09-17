#include "Number/Number.h"
#include <iostream>


int main(){
    auto number1 = Number(11);
    auto number2 = Number(2.33333);

    std::cout << "------------Number Tests--------------" << std::endl;

    std::cout << number1 + number2 << std::endl;
    std::cout << number1 + Numbers::zero << std::endl;
    std::cout << number1 + Numbers::one << std::endl;
    std::cout << number2 + Numbers::createNumber(2.66667) << std::endl;
    return 0;
}
