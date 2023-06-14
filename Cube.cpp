#include "cube.h"

Cube::Cube(const Vec3& minPoint, const Vec3& maxPoint)
    : minPoint(minPoint), maxPoint(maxPoint) {
    setAABB();
}

bool Cube::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {
    

    return false;
}

void Cube::setAABB() {
    boundingBox.maxPoint = maxPoint;
    boundingBox.minPoint = minPoint;
}
