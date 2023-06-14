#ifndef VOXELGRID_H
#define VOXELGRID_H

#include "vec3.h"
#include "ray.h"
#include "voxel.h"
#include "Hittable.h"

// VoxelGrid class declaration
class VoxelGrid {
public:
    int sizeX;
    int sizeY;
    int sizeZ;

    Voxel* voxels; //grid of voxels describing the scene
    Voxel mainVoxel;

    
    VoxelGrid(int sizeX, int sizeY, int sizeZ);
    VoxelGrid(int sizeX, int sizeY, int sizeZ, Vec3 minPoint, Vec3 maxPoint);
    ~VoxelGrid();

    Vec3 getVoxelSize() const;
    Vec3 getVoxelArrayIndexes(const Vec3& point) const;
    Voxel& getVoxel(int x, int y, int z);
    void calculateVoxelBounds();
    // Function for fast voxel traversal algorithm
    void traverseRay(const Ray& ray, HitRecord& record);
};

#endif // VOXELGRID_H
