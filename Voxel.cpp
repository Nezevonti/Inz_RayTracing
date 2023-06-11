#include "voxel.h"

Voxel::Voxel() : AABB(Vec3(), Vec3()), refractiveIndex(1.0f) {
    

}

Voxel::Voxel(const Vec3& minPoint, const Vec3& maxPoint, float refractiveIndex)
    : AABB(minPoint, maxPoint), refractiveIndex(refractiveIndex) {
    // Initialize any additional Voxel-specific members, if needed
}
