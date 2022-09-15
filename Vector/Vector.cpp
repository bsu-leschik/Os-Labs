#include "Vector.h"



Vector::Vector(Number x, Number y){
	_cords[0] = x;
	_cords[1] = y;
}

Number Vector::getR() {
	return Number(std::sqrt(pow(_cords[0].getNumber(), 2) + pow(_cords[1].getNumber(), 2)));
}

Number Vector::getAngle() {
	Number r = Number(std::sqrt(pow(_cords[0].getNumber(), 2) + pow(_cords[1].getNumber(), 2)));
	Number sin = _cords[1] / r;
	return Number(asin(sin.getNumber()));
}

Number VECTOR_API Vector::getX()
{
	return _cords[0];
}

Number VECTOR_API Vector::getY()
{
	return _cords[1];
}

Vector Vector::add(Vector vec1, Vector vec2) {
	Number x = vec1._cords[0] + vec2._cords[0];
	Number y = vec1._cords[1] + vec2._cords[1];
	Vector result = Vector(x, y);
	return result;
}

std::ostream& operator<<(std::ostream& os, const Vector& number) {
	os << number._cords[0] << " " << number._cords[1];
	return os;
}