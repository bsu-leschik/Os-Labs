#include "Number.h"

Number::Number(double number) {
	_number = number;
}

void Number::changeNumber(double newNumber) {
	_number = newNumber;
}

int Number::getNumber() {
	return _number;
}

Number& operator+(Number number1, Number number2)
{
	Number result = Number(number1._number + number2._number);
	return result;
}

Number& operator-(Number number1, Number number2)
{
	Number result = Number(number1._number - number2._number);
	return result;
}

Number& operator*(Number number1, Number number2)
{
	Number result = Number(number1._number * number2._number);
	return result;
}

Number& operator/(Number number1, Number number2)
{
	Number result = Number(number1._number / number2._number);
	return result;
}

std::ostream& operator<<(std::ostream& os, const Number& number)
{
	os << number._number;
	return os;
}
