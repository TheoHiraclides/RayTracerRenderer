#pragma once

#include <math.h>

#include "Vector.h"
#include "Ray.h"

class Material {
public:
    Vector albedo;
    Vector emissivity;
    double specularity;
    double opacity;

    Material(Vector albedo = Vector(1.0, 1.0, 1.0), Vector emissivity = Vector(), double specularity = 0.0, double opacity = 1.0) : albedo(albedo), emissivity(emissivity), specularity(specularity), opacity(opacity) {};
};

class Intersect {
public:
    bool result;
    double distance;
    int id;

    Intersect() { result = false; }
    Intersect(double d, int i) { distance = d; id = i;  result = true; }
};

class Sphere {
public:
	Vector center;
	double radius;
    Material material;
    int id;

    explicit Sphere(Vector c, double r = 1.0, Material m = Material(), int i = 0) { center = c; radius = r; material = m; id = i;  }

	bool intersect(const Ray& ray);
    Intersect getIntersection(const Ray& r);
};