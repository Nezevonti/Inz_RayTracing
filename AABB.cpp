#include "aabb.h"
#include <cmath>


AABB::AABB(const Vec3& minPoint, const Vec3& maxPoint)
    : minPoint(minPoint), maxPoint(maxPoint) {}

Vec3 AABB::calculateIntersectionPoint(const Ray& ray, float t) const {
    return Vec3(ray.origin.x + t * ray.direction.x,
        ray.origin.y + t * ray.direction.y,
        ray.origin.z + t * ray.direction.z);
}

bool AABB::intersect(const Ray& ray, float& tmin, float& tmax, Vec3& intersectionPoint, AABB_Face& intersectionFace) const {

    //Uses : Fast, Branchless Ray/Bounding Box Intersections
    //From : https://tavianator.com/2011/ray_box.html

    float t1[3];
    float t2[3];
    float tmin_direction[3];
    float tmax_direction[3];
    float tmin_overall = -INFINITY;
    float tmax_overall = INFINITY;

    for (int i = 0; i < 3; i++) {
        t1[i] = (minPoint[i] - ray.origin[i]) * ray.direction_inverse[i];
        t2[i] = (maxPoint[i] - ray.origin[i]) * ray.direction_inverse[i];

        tmin_direction[i] = (t1[i] < t2[i]) ? t1[i] : t2[i];
        tmax_direction[i] = (t1[i] > t2[i]) ? t1[i] : t2[i];

        tmin_overall = (tmin_overall > tmin_direction[i]) ? tmin_overall : tmin_direction[i];
        tmax_overall = (tmax_overall < tmax_direction[i]) ? tmax_overall : tmax_direction[i];
    }

    if (tmax_overall >= tmin_overall && tmax_overall >= 0) {
        intersectionPoint = calculateIntersectionPoint(ray, tmin_overall);

        if(tmin_overall == tmin_direction[0])
            intersectionFace = AABB_FACE_X_MIN;
        else if (tmin_overall == tmin_direction[1])
            intersectionFace = AABB_FACE_Y_MIN;
        else if (tmin_overall == tmin_direction[2])
            intersectionFace = AABB_FACE_Z_MIN;
        else if (tmin_overall == tmax_direction[0])
            intersectionFace = AABB_FACE_X_MAX;
        else if (tmin_overall == tmax_direction[1])
            intersectionFace = AABB_FACE_Y_MAX;
        else if (tmin_overall == tmax_direction[2])
            intersectionFace = AABB_FACE_Z_MAX;

        return true;
    }
    return false;
}

std::string AABB::getFaceName(AABB_Face face) {
    switch (face) {
    case AABB_FACE_X_MIN:
        return "X_MIN";
    case AABB_FACE_X_MAX:
        return "X_MAX";
    case AABB_FACE_Y_MIN:
        return "Y_MIN";
    case AABB_FACE_Y_MAX:
        return "Y_MAX";
    case AABB_FACE_Z_MIN:
        return "Z_MIN";
    case AABB_FACE_Z_MAX:
        return "Z_MAX";
    default:
        return "NONE";
    }
}

Vec3 AABB::getFaceNormal(AABB_Face face) {
    switch (face) {
    case AABB_FACE_X_MIN:
        return Vec3(-1, 0, 0);
    case AABB_FACE_X_MAX:
        return Vec3(1, 0, 0);
    case AABB_FACE_Y_MIN:
        return Vec3(0, -1, 0);
    case AABB_FACE_Y_MAX:
        return Vec3(0, 1, 0);
    case AABB_FACE_Z_MIN:
        return Vec3(0, 0, -1);
    case AABB_FACE_Z_MAX:
        return Vec3(0, 0, 1);
    default:
        return Vec3(0, 0, 0);
    }
}
