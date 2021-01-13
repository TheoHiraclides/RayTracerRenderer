#pragma once

#include "Ray.h"

class Camera {
public:
	int height;
	int width;
	double fov;
	Vector position;

	Camera(Vector p = Vector(0, 0, 70), int h = 512, int w = 512, double f = 60.0) { position = p, height = h, width = w, fov = f; }

	Ray getRay(int i, int j);
};