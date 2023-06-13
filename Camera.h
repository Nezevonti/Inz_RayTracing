#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"
#include "VoxelGrid.h"

class Camera {
public:
    Vec3 position;
    Vec3 direction;
    Vec3 up;
    float fov;

    int imageWidth = 640;
    int imageHeight = 480;

    Vec3* pixelArray;

    Camera(const Vec3& position, const Vec3& target, const Vec3& up, float fov);

    Ray getRay(int pixelX, int pixelY) const;

    Vec3* getPixels();

    void setPixel(int x, int y,Vec3 pixelColors);

    void draw(VoxelGrid scene);
};

#endif // CAMERA_H
