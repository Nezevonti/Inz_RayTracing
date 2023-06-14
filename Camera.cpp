#include "camera.h"
#include "Hittable.h"
#include <cmath>
#include <Windows.h>
#include <iostream>


Camera::Camera(const Vec3& position, const Vec3& target, const Vec3& up, float fov)
    : position(position), up(up), fov(fov)
{
    direction = (target - position).normalize();

    int numPixels = imageHeight * imageWidth;
    pixelArray = new Vec3[numPixels];


    aspectRatio = static_cast<float>(imageWidth) / imageHeight;
    halfWidth = tan(fov / 2);
    halfHeight = halfWidth / aspectRatio;

    right = direction.cross(up).normalize();
    upNormalized = up.normalize();
}

float Camera::randFloat() const{
    return rand() / (RAND_MAX + 1.0);
}

Ray Camera::getRay(int pixelX, int pixelY) const {
    /*
    float aspectRatio = static_cast<float>(imageWidth) / imageHeight;
    float halfWidth = tan(fov / 2);
    float halfHeight = halfWidth / aspectRatio;

    Vec3 right = direction.cross(up).normalize();
    Vec3 upNormalized = up.normalize();
    */

    float u = static_cast<float>(pixelX) / (imageWidth - 1);
    float v = 1 - static_cast<float>(pixelY) / (imageHeight - 1);

    Vec3 rayDirection = direction + right * halfWidth * (2 * u - 1) + upNormalized * halfHeight * (2 * v - 1);
    return Ray(position, rayDirection);
}

Ray Camera::getRay(float u, float v) const {
    Vec3 rayDirection = direction + right * halfWidth * (2 * u - 1) + upNormalized * halfHeight * (2 * v - 1);
    return Ray(position, rayDirection);
}

Vec3* Camera::getPixels() {
    return pixelArray;
}

void Camera::setPixel(int x, int y, Vec3 pixelColors){
    if(x<0 || x>= imageWidth) throw std::out_of_range("index out of range");
    if (y < 0 || y >= imageHeight) throw std::out_of_range("index out of range");

    pixelArray[y * imageHeight + x] = pixelColors;
}

void Camera::draw(VoxelGrid scene){

    Vec3 pixel;
    Vec3 sumPixel;

    Vec3 intersectionPoint(0, 0, 0);
    AABB_Face intersectionFace;

    HitRecord record;

    
    

    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {

            //float u = (x + randFloat()) / (imageWidth - 1);
            //float v = 1 - (y + randFloat()) / (imageHeight - 1);
            float tmin = -INFINITY;
            float tmax = INFINITY;

            Ray ray = getRay(x, y);

            // Chceck if ray even hits the voxelGrid
            bool intersect = scene.mainVoxel.intersect(ray, intersectionPoint, intersectionFace,tmin,tmax);
            if (intersect) { 
                scene.traverseRay(ray,record);

                //hit grid but nothing inside
                if (record.t > tmax || record.t < tmin) {
                    //background color
                    pixel.x = 0;
                    pixel.y = 0;
                    pixel.z = 0;

                    continue;
                }
                pixel = record.normal;
                pixel = pixel.mapToUnitRange();
            }
            else {
                //background color
                pixel.x = 0;
                pixel.y = 0;
                pixel.z = 0;
            }

            // Assign the calculated pixel color

            pixelArray[y * imageWidth + x] = pixel;
            //TYMCZASOWE_END


        }
    }



}
