#include "Scene.h"

#include <iostream>
#include <random>
#include <cmath>

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

double Scene::getLightObstruction(Vector intersection, Vector toLightNormalized, double distance_sqr)
{
    Intersect intersect = getIntersect(Ray(intersection, toLightNormalized));

    if (!intersect.result || std::pow(intersect.distance, 2) > distance_sqr) {
        return 1.0;
    } else {
        return 0.0;
        if (spheres[intersect.id].material.opacity >= 1.0) {
            return 0.0;
        } else {
            double epsilon = 0.00000001;

            Vector intersection = intersection + intersect.distance * toLightNormalized;

            Vector toLight = (light - intersection);

            return std::sqrt(1 - spheres[intersect.id].material.opacity) * getLightObstruction(intersection + toLightNormalized * epsilon, toLightNormalized, toLight.sqrNorm());
        }
    }
}

Vector Scene::getColor(const Ray& ray, int rebounds) {
	Vector color = Vector();
    if (rebounds >= settings.max_rebounds) return color;
	
    Intersect intersect = getIntersect(ray);

    double epsilon = 0.00000001;

    if (intersect.result) {
        Vector intersection = ray.center + intersect.distance * ray.direction;

        Vector normal = (intersection - spheres[intersect.id].center) / spheres[intersect.id].radius;

        Vector toLight = (light - intersection);
        Vector toLightNormalized = toLight.get_normalized();

        double light_obstruction = getLightObstruction(intersection + toLightNormalized * epsilon, toLightNormalized, toLight.sqrNorm());

        color = light_obstruction * spheres[intersect.id].material.albedo * std::max(0.0, dot(toLightNormalized, normal) / toLight.sqrNorm());

        /* Intersect light_intersection = getIntersect(Ray(intersection + normal * epsilon, toLightNormalized));
        if (!light_intersection.result || std::pow(light_intersection.distance, 2) > toLight.sqrNorm()) {
            color = spheres[intersect.id].material.albedo * std::max(0.0, dot(toLightNormalized, normal) / toLight.sqrNorm());
            if (rebounds >= settings.max_rebounds) color = color * spheres[intersect.id].material.opacity;
        } */

        if (spheres[intersect.id].material.opacity > 0.0 && spheres[intersect.id].material.specularity < 1.0) {
            std::uniform_real_distribution<double> distrib(0, 1);

            double u1 = distrib(engine);
            double u2 = distrib(engine);

            Ray next_ray = Ray(intersection + normal * epsilon, random_cos(normal, u1, u2));

            color = color + multiply(spheres[intersect.id].material.albedo, getColor(next_ray, rebounds + 1));
        }

        if (spheres[intersect.id].material.specularity > 0.0) {
            color = (1 - spheres[intersect.id].material.specularity) * color;
            Vector reflect = ray.direction - 2 * dot(ray.direction, normal) * normal;
            Ray reflected_ray = Ray(intersection + normal * epsilon, reflect);
            color = color + spheres[intersect.id].material.specularity * getColor(reflected_ray, rebounds + 1);
        }

        if (spheres[intersect.id].material.opacity < 1.0) {
            color = spheres[intersect.id].material.opacity * color;
            double refractivity = spheres[intersect.id].material.refractivity;
            if (dot(ray.direction, normal) < 0.0) {
                // std::cout << "switched/ ";
                refractivity = 1 / refractivity;
            }
            else {
                normal = -1 * normal;
            }
            double root = 1 - std::pow(refractivity, 2) * (1 - std::pow(dot(ray.direction, normal), 2));
            if (root <= 0) {
                // std::cout << "reflected" << rebounds << "//" << intersect.distance << "/" << intersect.id << ": ";
                // std::cout << intersection[0] << "/" << intersection[1] << "/" << intersection[2] << "\n";
                Vector reflect = ray.direction - 2 * dot(ray.direction, normal) * normal;
                Ray reflected_ray = Ray(intersection + normal * epsilon, reflect);
                color = color + (1 - spheres[intersect.id].material.opacity) * getColor(reflected_ray, rebounds + 1);
            }
            else {
                Vector refract = refractivity * ray.direction - (refractivity * dot(ray.direction, normal) + std::sqrt(root)) * normal;
                Ray refracted_ray = Ray(intersection + refract * epsilon, refract);
                /* std::cout << "refracted: " << rebounds << "//" << intersect.distance << "/" << intersect.id <<": ";
                std::cout << intersection[0] << "/" << intersection[1] << "/" << intersection[2] << " :: ";
                std::cout << ray.direction[0] << "/" << ray.direction[1] << "/" << ray.direction[2] << " ::: ";
                std::cout << refract[0] << "/" << refract[1] << "/" << refract[2] << "\n"; */
                color = color + (1 - spheres[intersect.id].material.opacity) * getColor(refracted_ray, rebounds + 1);
            }
        }
    }

    return color;
}

std::vector<unsigned char> Scene::getImage(int  N) {
    std::vector<double> rawImage(camera.height * camera.width * 3, 0.0);
    double maxColor = 0.0;

    #pragma fomp parallel for schedule(dynamic,1);
    for (int i = 0; i < camera.height; i++) {
        for (int j = 0; j < camera.width; j++) {
            Vector color = Vector();
            for (int k = 0; k < N; k++) {
                color = color + getColor(camera.getRay(i, j));
            }
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