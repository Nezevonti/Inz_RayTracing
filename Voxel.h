#ifndef VOXEL_H
#define VOXEL_H

#include "aabb.h"


class Voxel : public AABB {
public:
    float refractiveIndex;

    Voxel();
    Voxel(const Vec3& minPoint, const Vec3& maxPoint, float refractiveIndex);
};

#endif // VOXEL_H
