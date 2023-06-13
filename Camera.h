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

    Ray getRay(float u, float v) const;

    Vec3* getPixels();

    void setPixel(int x, int y,Vec3 pixelColors);

    void draw(VoxelGrid scene);

private : 
    Vec3 right;
    Vec3 upNormalized;

    float aspectRatio;
    float halfWidth;
    float halfHeight;

    float randFloat() const;
};

#endif // CAMERA_H
