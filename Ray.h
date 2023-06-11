#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;
    Vec3 direction_inverse;

    Ray(const Vec3& _rigin, const Vec3& direction);
};

#endif  // RAY_H