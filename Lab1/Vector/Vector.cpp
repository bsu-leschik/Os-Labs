#include "Vector.h"
#include <cmath>

Vector::Vector(Number x, Number y){
    _cords[0] = x;
    _cords[1] = y;
}

Number Vector::getR() {
    Number x = _cords[0] * _cords[0];
    Number y = _cords[1] * _cords[1];
    return {std::sqrt(x.getNumber() + y.getNumber())};
}

Number Vector::getAngle() {
    Number sin = _cords[1] / this->getR();
    return {asin(sin.getNumber())};
}

Number Vector::getX()
{
    return _cords[0];
}

Number Vector::getY()
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