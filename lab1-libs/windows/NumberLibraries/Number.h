#pragma once

#include <iostream>
#include <ostream>

class Number
{
private:

	double _number;

public:

	Number(double number);

	Number() = default;

	void changeNumber(double newNumber);

	double getNumber();

	friend Number& operator+(Number number1, Number number2);

	friend Number& operator-(Number number1, Number number2);
	
	friend Number& operator*(Number number1, Number number2);
	
	friend Number& operator/(Number number1, Number number2);

	friend std::ostream& operator<<(std::ostream& os, const Number& number);

	
};


namespace Numbers {
	const Number zero = Number(0);
	const Number one = Number(1);

	inline Number createNumber(double num) {
		return Number(num);
	}
}