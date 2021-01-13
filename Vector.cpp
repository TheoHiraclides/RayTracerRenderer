#include "Vector.h"

Vector Vector::get_normalized() {
	double norm = sqrt(sqrNorm());
	return Vector(coords[0] / norm, coords[1] / norm, coords[2] / norm);
}

double const Vector::dot(const Vector& v) {
	return coords[0] * v.coords[0] + coords[1] * v.coords[1] + coords[2] * v.coords[2];
}

Vector operator+(const Vector& v1, const Vector& v2) {
	return Vector(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

Vector operator-(const Vector& v1, const Vector& v2) {
	return Vector(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

Vector operator*(double d, const Vector& v) {
	return Vector(d * v[0], d * v[1], d * v[2]);
}

Vector operator*(const Vector& v, double d) {
	return Vector(d * v[0], d * v[1], d * v[2]);
}

Vector operator/(const Vector& v, double d) {
	return Vector(v[0] / d, v[1] / d, v[2] / d);
}

double dot(const Vector& v1, const Vector& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

Vector multiply(const Vector& v1, const Vector& v2) {
	return Vector(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}