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

Vector cross(const Vector& v1, const Vector& v2) {
	return Vector(v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0]);
}

Vector random_cos(const Vector& n, double u1, double u2) {
	double x = std::cos(2 * 3.1415 * u1) * std::sqrt(1 - u2);
	double y = std::sin(2 * 3.1415 * u1) * std::sqrt(1 - u2);
	double z = std::sqrt(u2);
	Vector t1;
	if (n[0] < n[1] && n[1] < n[0]) {
		t1 = Vector(0, n[2], -n[1]);
	}
	else if (n[1] > n[2] && n[1] < n[0]) {
		t1 = Vector(n[2], 0, -n[0]);
	}
	else {
		t1 = Vector(n[1], -n[0], 0);
	}
	t1 = t1.get_normalized();
	Vector t2 = cross(n, t2);
	return z * n + x * t1 + y * t2;
}