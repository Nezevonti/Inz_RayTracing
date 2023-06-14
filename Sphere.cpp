#include "sphere.h"


Sphere::Sphere(const Vec3& center, float radius)
    : center(center), radius(radius){
    setAABB();
}

bool Sphere::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {
    Vec3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float root = sqrt(discriminant);
        float t = (-b - root) / a;
        if (t < tMax && t > tMin) {
            record.t = t;
            record.intersectionPoint = ray.at(t);
            Vec3 outwardNormal = (record.intersectionPoint - center) * (1/radius);
            record.setFaceNormal(ray, outwardNormal);
            return true;
        }
        t = (-b + root) / a;
        if (t < tMax && t > tMin) {
            record.t = t;
            record.intersectionPoint = ray.at(t);
            Vec3 outwardNormal = (record.intersectionPoint - center) * (1/radius);
            record.setFaceNormal(ray, outwardNormal);
            return true;
        }
    }

    return false;
}

void Sphere::setAABB() {
    Vec3 radiusVector(radius+FLT_EPSILON, radius + FLT_EPSILON, radius + FLT_EPSILON);
    Vec3 minPoint = center - radiusVector;
    Vec3 maxPoint = center + radiusVector;

    boundingBox = AABB(minPoint, maxPoint);
}
