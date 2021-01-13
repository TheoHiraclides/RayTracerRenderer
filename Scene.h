#pragma once

#include <vector>
#include <algorithm>

#include "Sphere.h"
#include "Camera.h"

class SceneSettings {
public:
	int max_rebounds;

	SceneSettings(int rebounds = 10) { max_rebounds = rebounds; }
};

class Scene {
public:
	Vector light;
	std::vector<Sphere> spheres;
	Camera camera;
	SceneSettings settings;

	Scene(Camera c = Camera(), Vector l = Vector(5, 5, 25), SceneSettings scene_settings = SceneSettings()) { camera = c; light = l; settings = scene_settings; }
	
	void addSphere(Sphere sphere) { sphere.id = spheres.size(); spheres.push_back(sphere); }
	void addSphere(Vector c, double r = 1.0, Material m = Material()) { spheres.push_back(Sphere(c, r, m, spheres.size())); }

	std::vector<unsigned char> getImage();
	
	Vector getColor(const Ray& ray, int rebounds = 0);
	Intersect getIntersect(const Ray& ray);

	double getLightObstruction(Vector intersection, Vector toLightNormalized, double distance_sqr);
};