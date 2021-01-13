#include "Scene.h"

#include <iostream>

Intersect Scene::getIntersect(const Ray& ray) {
    Intersect intersect_result = Intersect();
    for (unsigned int i = 0; i < spheres.size(); i++) {
        Intersect new_intersect = spheres[i].getIntersection(ray);
        if ((!intersect_result.result && new_intersect.result) || (intersect_result.result && new_intersect.distance < intersect_result.distance)) {
            intersect_result = new_intersect;
        }
    }
    return intersect_result;
}

Vector Scene::getColor(const Ray& ray, int rebounds) {
	Vector color = Vector();
	
    Intersect intersect = getIntersect(ray);

    if (intersect.result) {
        Vector intersection = ray.center + intersect.distance * ray.direction;

        Vector normal = (intersection - spheres[intersect.id].center) / spheres[intersect.id].radius;

        Vector toLight = (light - intersection);
        Vector toLightNormalized = toLight.get_normalized();

        Intersect light_intersection = getIntersect(Ray(intersection + normal*0.000001, toLightNormalized));
        if (!light_intersection.result || std::pow(light_intersection.distance, 2) > toLight.sqrNorm()) {
            color = spheres[intersect.id].material.albedo * std::max(0.0, dot(toLightNormalized, normal) / toLight.sqrNorm());
        }

        if (spheres[intersect.id].material.specularity > 0.0 && rebounds < settings.max_rebounds) {
            color = (1 - spheres[intersect.id].material.specularity) * color;
            Vector reflect = ray.direction - 2 * dot(ray.direction, normal) * normal;
            Ray reflected_ray = Ray(intersection + normal * 0.000001, reflect);
            color = color + spheres[intersect.id].material.specularity * getColor(reflected_ray, rebounds + 1);
        }
    }

    return color;
}

std::vector<unsigned char> Scene::getImage() {
    std::vector<double> rawImage(camera.height * camera.width * 3, 0.0);
    double maxColor = 0.0;

    for (int i = 0; i < camera.height; i++) {
        for (int j = 0; j < camera.width; j++) {
            Vector color = getColor(camera.getRay(i, j));
            rawImage[(i*camera.height + j) * 3] = color[0];
            maxColor = std::max(maxColor, color[0]);
            rawImage[(i * camera.height + j) * 3 + 1] = color[1];
            maxColor = std::max(maxColor, color[1]);
            rawImage[(i * camera.height + j) * 3 + 2] = color[2];
            maxColor = std::max(maxColor, color[2]);
        }
    }

    double gamma = 2.2;

    std::vector<unsigned char> image(camera.height * camera.width * 3, 0);
    for (int i = 0; i < rawImage.size(); i++) {
        image[i] = int(pow(rawImage[i] / maxColor, 1/gamma) * 255);
    }

    return image;
}