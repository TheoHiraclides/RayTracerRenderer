#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <chrono>

#include "Scene.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    int W = 512;
    int H = W;

    Scene scene = Scene(Camera(Vector(0, 0, 70), H, W));
    /*scene.addSphere(Vector(0, 20, 0), 15.0, Material(Vector(1.0, 0.0, 0.0), Vector(), 0.0, 0.0));
    scene.addSphere(Vector(0, 0, -10000), 9940.0, Material(Vector(0.0, 1.0, 0.0)));
    scene.addSphere(Vector(0, 10000, 0), 9960.0, Material(Vector(1.0, 0.0, 1.0), Vector(), 0.0));
    scene.addSphere(Vector(10000, 0, 0), 9960.0, Material(Vector(0.0, 1.0, 1.0), Vector(), 0.0));
    scene.addSphere(Vector(-10000, 0, 0), 9960.0, Material(Vector(0.0, 0.0, 1.0), Vector(), 0.0));
    scene.addSphere(Vector(0, -10000, 0), 9960.0, Material(Vector(1.0, 1.0, 0.0)));
    scene.addSphere(Vector(25, 20, -25), 10.0, Material(Vector(1.0, 1.0, 1.0), Vector(), 1.0));*/

    scene.addSphere(Vector(0, 20, 0), 15.0, Material(Vector(1.0, 0.0, 0.0), Vector(), 0.0, 0.0));
    scene.addSphere(Vector(0, 0, -10000), 9940.0, Material(Vector(0.0, 1.0, 0.0)));
    scene.addSphere(Vector(0, 10000, 0), 9960.0, Material(Vector(1.0, 0.0, 1.0), Vector(), 0.0, 0.5));
    scene.addSphere(Vector(10000, 0, 0), 9960.0, Material(Vector(0.0, 1.0, 1.0), Vector(), 0.0, 0.0));
    scene.addSphere(Vector(-10000, 0, 0), 9960.0, Material(Vector(0.0, 0.0, 1.0), Vector(), 0.0, 0.8));
    scene.addSphere(Vector(0, -10000, 0), 9960.0, Material(Vector(1.0, 1.0, 0.0)));
    scene.addSphere(Vector(25, 20, -25), 10.0, Material(Vector(1.0, 1.0, 1.0), Vector(),  1.0));

    std::vector<unsigned char> image2 = scene.getImage();

    stbi_write_png("image.png", W, H, 3, &image2[0], 0);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    return 0;
}