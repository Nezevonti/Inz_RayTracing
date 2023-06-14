#include "voxel.h"

Voxel::Voxel() : AABB(Vec3(), Vec3()), refractiveIndex(1.0f) {
    
    occupied = false;
}

Voxel::Voxel(const Vec3& minPoint, const Vec3& maxPoint, float refractiveIndex)
    : AABB(minPoint, maxPoint), refractiveIndex(refractiveIndex) {
    occupied = false;

}
