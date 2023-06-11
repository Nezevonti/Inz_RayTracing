#include "voxelgrid.h"

// Include the Voxel class header
#include "voxel.h"

// VoxelGrid constructor implementation
VoxelGrid::VoxelGrid(int _sizeX, int _sizeY, int _sizeZ)
    : sizeX(_sizeX), sizeY(_sizeY), sizeZ(_sizeZ) {
    int numVoxels = sizeX * sizeY * sizeZ;
    voxels = new Voxel[numVoxels];
}

// VoxelGrid destructor implementation
VoxelGrid::~VoxelGrid() {
    delete[] voxels;
}

void VoxelGrid::traverseRay(const Ray& ray) {
    // Compute the ray direction in voxel coordinates
    int stepX = (ray.direction.x >= 0) ? 1 : -1;
    int stepY = (ray.direction.y >= 0) ? 1 : -1;
    int stepZ = (ray.direction.z >= 0) ? 1 : -1;

    // Calculate the initial cell coordinates
    int currentX = static_cast<int>(ray.origin.x);
    int currentY = static_cast<int>(ray.origin.y);
    int currentZ = static_cast<int>(ray.origin.z);

    // Calculate the tDelta values
    float tDeltaX = std::abs(1.0f / ray.direction.x);
    float tDeltaY = std::abs(1.0f / ray.direction.y);
    float tDeltaZ = std::abs(1.0f / ray.direction.z);

    // Calculate the tMax values
    float tMaxX = tDeltaX * 0.5f;
    float tMaxY = tDeltaY * 0.5f;
    float tMaxZ = tDeltaZ * 0.5f;

    // Perform the voxel traversal loop
    while (currentX >= 0 && currentX < sizeX &&
        currentY >= 0 && currentY < sizeY &&
        currentZ >= 0 && currentZ < sizeZ) {
        // Process the current cell (e.g., perform intersection test, update voxel data, etc.)
        // ...

        // Determine the next axis to step along based on the tMax values
        if (tMaxX < tMaxY) {
            if (tMaxX < tMaxZ) {
                currentX += stepX;
                tMaxX += tDeltaX;
            }
            else {
                currentZ += stepZ;
                tMaxZ += tDeltaZ;
            }
        }
        else {
            if (tMaxY < tMaxZ) {
                currentY += stepY;
                tMaxY += tDeltaY;
            }
            else {
                currentZ += stepZ;
                tMaxZ += tDeltaZ;
            }
        }

        // Update the ray parameter (t) based on the chosen axis and the new tMax value
        // ...

        // Check for intersection or termination conditions
        // ...

        // Repeat the loop
    }
}

