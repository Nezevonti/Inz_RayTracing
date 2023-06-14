#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
public:
    Vec3 center;
    float radius;

    Sphere() : Hittable() {};
    Sphere(const Vec3& center, float radius);

    bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;
    void setAABB() override;
};

#endif  // SPHERE_H
