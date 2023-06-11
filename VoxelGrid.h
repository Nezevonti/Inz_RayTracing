#ifndef VOXELGRID_H
#define VOXELGRID_H

#include "vec3.h"
#include "ray.h"

// Forward declaration of the Voxel class
class Voxel;

// VoxelGrid class declaration
class VoxelGrid {
public:
    int sizeX;
    int sizeY;
    int sizeZ;
    Voxel* voxels;

    
    VoxelGrid(int sizeX, int sizeY, int sizeZ);
    ~VoxelGrid();

    // Function for fast voxel traversal algorithm
    void traverseRay(const Ray& ray);
};

#endif // VOXELGRID_H
