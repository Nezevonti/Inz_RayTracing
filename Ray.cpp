#include "ray.h"

Ray::Ray(const Vec3& _origin, const Vec3& _direction)
    : origin(_origin), direction(_direction),
    direction_inverse(1.0f / _direction.x, 1.0f / _direction.y, 1.0f / _direction.z) {}
