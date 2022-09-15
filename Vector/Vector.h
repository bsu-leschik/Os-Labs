#pragma once

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif



#include "Number.h"
#include <cmath>

extern "C" VECTOR_API class Vector
{
private:
	Number _cords[2];
	
public:

	VECTOR_API Vector(Number x, Number y);

	Number VECTOR_API convertXToPolar();

	Number VECTOR_API convertYToPolar();

	static Vector VECTOR_API add(Vector & vec1, Vector & vec2);

	friend VECTOR_API std::ostream& operator<<(std::ostream& os, const Vector& number);
};

namespace Vectors{
	const Vector zero = Vector(Number(0), Number(0));
	const Vector one = Vector(Number(1), Number(1));
}

