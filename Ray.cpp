#include "ray.h"

Ray::Ray(const Vec3& origin, const Vec3& direction)
    : origin(origin), direction(direction),
    direction_inverse(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z) {}
