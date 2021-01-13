#pragma once

#include <math.h>
#include <iostream>

class Vector {

public:
	double coords[3];
	explicit Vector(double x=0, double y=0, double z=0) { coords[0] = x; coords[1] = y; coords[2] = z; }


	double operator[](int i) const { return coords[i]; };
	double& operator[](int i) { return coords[i]; }

	double sqrNorm() const { return coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]; }
	Vector get_normalized();
	double const dot(const Vector& v);

	const void print() { std::cout << "(" << coords[0] << ", " << coords[1] << ", " << coords[2] << ")"; }
};

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator*(double d, const Vector& v);
Vector operator*(const Vector& v, double d);
Vector operator/(const Vector& v, double d);

double dot(const Vector& v1, const Vector& v2);
Vector multiply(const Vector& v1, const Vector& v2);