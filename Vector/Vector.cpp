#include "Vector.h"



Vector::Vector(Number x, Number y){
	_cords[0] = x;
	_cords[1] = y;
}

Number Vector::convertXToPolar() {
	Number r = Number(std::sqrt(pow(_cords[0].getNumber(), 2) + pow(_cords[1].getNumber(), 2)));
	Number cos = _cords[0] / r;
	return r * cos;
}

Number Vector::convertYToPolar() {
	Number r = Number(std::sqrt(pow(_cords[0].getNumber(), 2) + pow(_cords[1].getNumber(), 2)));
	Number sin = _cords[1] / r;
	return r * sin;
}

Vector Vector::add(Vector& vec1, Vector& vec2) {
	Vector result = Vector(vec1._cords[0] + vec2._cords[0], vec1._cords[1] + vec2._cords[1]);
	return result;
}

std::ostream& operator<<(std::ostream& os, const Vector& number) {
	os << number._cords[0] << " " << number._cords[1];
	return os;
}