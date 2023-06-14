#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"

class Cube : public Hittable {
public:
    Vec3 minPoint;
    Vec3 maxPoint;

    Cube(const Vec3& minPoint, const Vec3& maxPoint);

    bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;
    void setAABB() override;
};

#endif  // CUBE_H
