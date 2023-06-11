#ifndef VOXEL_H
#define VOXEL_H

#include "aabb.h"


class Voxel : public AABB {
public:
    float refractiveIndex;

    Voxel();
    Voxel(const Vec3& _minPoint, const Vec3& _maxPoint, float _refractiveIndex);
};

#endif // VOXEL_H
