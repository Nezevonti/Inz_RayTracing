#include "camera.h"
#include <cmath>
#include <Windows.h>
#include <iostream>

Camera::Camera(const Vec3& position, const Vec3& target, const Vec3& up, float fov)
    : position(position), up(up), fov(fov)
{
    direction = (target - position).normalize();

    int numPixels = imageHeight * imageWidth;
    pixelArray = new Vec3[numPixels];
}

Ray Camera::getRay(int pixelX, int pixelY) const { //It gets pixels from the bottom left, not the top left as it should.
    float aspectRatio = static_cast<float>(imageWidth) / imageHeight;
    float halfWidth = tan(fov / 2);
    float halfHeight = halfWidth / aspectRatio;

    Vec3 right = direction.cross(up).normalize();
    Vec3 upNormalized = up.normalize();

    float u = static_cast<float>(pixelX) / (imageWidth - 1);
    float v = static_cast<float>(pixelY) / (imageHeight - 1);

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

    Vec3 intersectionPoint(0, 0, 0);
    AABB_Face intersectionFace;
    
    char buffer[100];


    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            Ray ray = getRay(x, y);

            // Do something with the ray (e.g., trace it and calculate pixel color)
            // ...
            
            


            bool intersect = scene.mainVoxel.intersect(ray, intersectionPoint, intersectionFace);
            if (intersect) {
                pixel = scene.mainVoxel.getFaceNormal(intersectionFace);
                
                if (pixel.x < 0)pixel.x = 1;
                if (pixel.y < 0)pixel.y = 1;
                if (pixel.z < 0)pixel.z = 1;

            }
            else {
                pixel.x = 0;
                pixel.y = 0;
                pixel.z = 0;
            }



            //sprintf_s(buffer, "(%f,%f,%f) %c\n", ray.direction.x, ray.direction.y, ray.direction.z, intersect ? 'T' : 'F');
            //OutputDebugStringA(buffer);
            
            // Assign the calculated pixel color to the canvas
            // canvas.setPixelColor(x, y, calculatedColor);

            //sprintf_s(buffer, "(%d,%d) - %d\n",x,y, y * imageHeight + x);
            //OutputDebugStringA(buffer);

            pixelArray[y * imageWidth + x] = pixel;
        }
    }

    /*
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 16; j++) {
            sprintf_s(buffer, "%c",bools[i][j] ? 'T' : 'F');
            OutputDebugStringA(buffer);
        }
        sprintf_s(buffer, "\n");
        OutputDebugStringA(buffer);
    }
    */

}
