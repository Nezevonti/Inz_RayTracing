#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"
#include "AABB.h"

struct HitRecord {
    Vec3 intersectionPoint;
    Vec3 normal;
    float t;
    bool frontFace;

    inline void setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
        frontFace = ray.direction.dot(outwardNormal) < 0;
        normal = frontFace ? outwardNormal : (outwardNormal*-1);
    }
};

class Hittable {
public:
    AABB boundingBox;

    Hittable() {};
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const = 0;
    virtual void setAABB() = 0;
};

#endif  // HITTABLE_H