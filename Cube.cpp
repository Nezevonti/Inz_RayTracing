#include "cube.h"

Cube::Cube(const Vec3& minPoint, const Vec3& maxPoint)
    : minPoint(minPoint), maxPoint(maxPoint) {
    setAABB();
}

//this NEEDS to be redone to handle non-axis aligned cubes or add new class just for that.
bool Cube::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {

    Vec3 tMinBound = (minPoint - ray.origin) * ray.direction_inverse;
    Vec3 tMaxBound = (maxPoint - ray.origin) * ray.direction_inverse;

    float tEnter = std::max({ tMinBound.x, tMinBound.y, tMinBound.z });
    float tExit = std::min({ tMaxBound.x, tMaxBound.y, tMaxBound.z });

    if (tEnter > tExit || tExit < tMin || tEnter > tMax) {
        return false;  // No intersection
    }

    float tHit = tEnter;
    record.normal = Vec3(-1, 0, 0);
    if (tMinBound.y > tHit) {
        tHit = tMinBound.y;
        record.normal = Vec3(0, -1, 0);
    }
    if (tMinBound.z > tHit) {
        tHit = tMinBound.z;
        record.normal = Vec3(0, 0, -1);
    }
    if (tMaxBound.x < tHit) {
        tHit = tMaxBound.x;
        record.normal = Vec3(1, 0, 0);
    }
    if (tMaxBound.y < tHit) {
        tHit = tMaxBound.y;
        record.normal = Vec3(0, 1, 0);
    }
    if (tMaxBound.z < tHit) {
        tHit = tMaxBound.z;
        record.normal = Vec3(0, 0, 1);
    }

    record.t = tHit;
    record.intersectionPoint = ray.at(tHit);

    return true;
}

void Cube::setAABB() {
    boundingBox.maxPoint = maxPoint;
    boundingBox.minPoint = minPoint;
}
