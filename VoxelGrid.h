#ifndef VOXELGRID_H
#define VOXELGRID_H

#include "vec3.h"
#include "ray.h"
#include "voxel.h"

// Forward declaration of the Voxel class


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

    Vec3 getVoxelArrayIndexes(const Vec3& point) const {
    // Function for fast voxel traversal algorithm
    void traverseRay(const Ray& ray);
};

#endif // VOXELGRID_H
