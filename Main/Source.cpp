#include "Vector.h"
#include <iostream>

int main() {
	Number number1 = Number(11);
	Number number2 = Number(2.33333);

	Vector vec1 = Vector(Numbers::one, Number(2));
	Vector vec2 = Vector(number1, Number(3.14));

	std::cout << "------------Number Tests--------------" << std::endl;

	std::cout << number1 + number2 << std::endl;
	std::cout << number1 + Numbers::zero << std::endl;
	std::cout << number1 + Numbers::one << std::endl;
	std::cout << number2 + Numbers::createNumber(2.66667) << std::endl;

	std::cout << "------------Vector Tests--------------" << std::endl;

	std::cout << vec1 << "///" << vec2 <<"----" << Vector::add(vec1, vec2) << std::endl;
	std::cout << vec1.convertXToPolar() << "-/-" << vec2.convertYToPolar() << std::endl;
	std::cout << Vectors::zero << "-/-" << Vectors::one << std::endl;

	return 0;
}