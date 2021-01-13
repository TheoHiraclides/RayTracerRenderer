#pragma once

#include "Vector.h"

class Ray {
public:
	Vector center;
	Vector direction;

	explicit Ray(Vector c, Vector d) { center = c; direction = d; }
};