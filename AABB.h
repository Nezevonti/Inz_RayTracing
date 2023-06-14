#ifndef AABB_H
#define AABB_H

#include <string>

#include "vec3.h"
#include "ray.h"

enum AABB_Face {
    AABB_FACE_NONE,
    AABB_FACE_X_MIN,
    AABB_FACE_X_MAX,
    AABB_FACE_Y_MIN,
    AABB_FACE_Y_MAX,
    AABB_FACE_Z_MIN,
    AABB_FACE_Z_MAX
};

class AABB {
public:
    Vec3 minPoint;
    Vec3 maxPoint;

    AABB();
    AABB(const Vec3& minPoint, const Vec3& maxPoint);

    Vec3 calculateIntersectionPoint(const Ray& ray, float t) const;

    bool intersect(const Ray& ray, Vec3& intersectionPoint, AABB_Face& intersectionFace) const;

    bool intersect(const Ray& ray, Vec3& intersectionPoint, AABB_Face& intersectionFace, float &tmin, float &tmax) const;

    static Vec3 getFaceNormal(AABB_Face face);

    std::string getFaceName(AABB_Face face);
};

#endif  // AABB_H
