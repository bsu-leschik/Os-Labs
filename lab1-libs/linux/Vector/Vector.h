#ifndef OS_LABS_VECTOR_H
#define OS_LABS_VECTOR_H

#include "../Number/Number.h"

class Vector {

private:
    Number _cords[2];

public:

    Vector(Number x, Number y);

    Number getR();

    Number getAngle();

    Number getX();

    Number getY();

    static Vector add(Vector vec1, Vector vec2);

    friend std::ostream& operator<<(std::ostream& os, const Vector& number);
};

namespace Vectors{
    const Vector zero = Vector(Number(0), Number(0));
    const Vector one = Vector(Number(1), Number(1));
}



#endif //OS_LABS_VECTOR_H
