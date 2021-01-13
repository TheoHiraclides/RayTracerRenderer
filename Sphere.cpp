#include "Sphere.h"

bool Sphere::intersect(const Ray& ray) {
	double b = 2 * dot(ray.direction, ray.center - center);
	double c = (ray.center - center).sqrNorm() - radius*radius;

	double delta = b * b - 4 * c;

	return (delta >= 0);
}

Intersect Sphere::getIntersection(const Ray& ray) {
	double b = 2 * dot(ray.direction, ray.center - center);
	double c = (ray.center - center).sqrNorm() - radius * radius;

	double delta = b * b - 4 * c;

	if (delta <= 0) { return Intersect(); }

	delta = sqrt(delta);

	double x = (-b - delta) / 2;

	if (x < 0) { x += delta; }
	if (x < 0) { return Intersect(); }

	return Intersect(x, this->id);
}