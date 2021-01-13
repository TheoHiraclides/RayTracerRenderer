#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

#include "Scene.h"

int main() {
    int W = 512;
    int H = 512;

    Scene scene = Scene();
    scene.addSphere(Vector(), 15.0);
    scene.spheres[0].material.albedo = Vector(1.0, 0.0, 0.0);
    scene.spheres[0].material.specularity = 0.5;

    scene.addSphere(Vector(0, 0, -10000), 9940.0);
    scene.spheres[1].material.albedo = Vector(0.0, 1.0, 0.0);

    scene.addSphere(Vector(0, 10000, 0), 9960.0);
    scene.spheres[2].material.albedo = Vector(1.0, 0.0, 1.0);

    scene.addSphere(Vector(10000, 0, 0), 9960.0);
    scene.spheres[3].material.albedo = Vector(0.0, 1.0, 1.0);

    scene.addSphere(Vector(-10000, 0, 0), 9960.0);
    scene.spheres[4].material.albedo = Vector(0.0, 0.0, 1.0);

    scene.addSphere(Vector(0, -10000, 0), 9960.0);
    scene.spheres[5].material.albedo = Vector(1.0, 1.0, 0.0);

    scene.addSphere(Vector(25, 20, -25), 10.0);
    scene.spheres[6].material.specularity = 1;

    std::vector<unsigned char> image2 = scene.getImage();

    stbi_write_png("image.png", W, H, 3, &image2[0], 0);

    return 0;
}