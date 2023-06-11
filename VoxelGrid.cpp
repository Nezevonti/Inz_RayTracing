#include "voxelgrid.h"

// Include the Voxel class header
#include "voxel.h"

// VoxelGrid constructor implementation
VoxelGrid::VoxelGrid(int sizeX, int sizeY, int sizeZ)
    : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {

    int numVoxels = sizeX * sizeY * sizeZ;
    voxels = new Voxel[numVoxels];

    mainVoxel = Voxel(Vec3(0, 0, 0), Vec3(sizeX, sizeY, sizeZ), 1.0);
}

VoxelGrid::VoxelGrid(int sizeX, int sizeY, int sizeZ, Vec3 minPoint, Vec3 maxPoint) 
    : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {

        int numVoxels = sizeX * sizeY * sizeZ;
        voxels = new Voxel[numVoxels];

        mainVoxel =  Voxel(minPoint, maxPoint, 1.0);

}

// VoxelGrid destructor implementation
VoxelGrid::~VoxelGrid() {
    delete[] voxels;
}

Vec3 VoxelGrid::getVoxelArrayIndexes(const Vec3& point) const {
    int indexX = static_cast<int>((point.x - mainVoxel.minPoint.x) / voxelSize);
    int indexY = static_cast<int>((point.y - mainVoxel.minPoint.y) / voxelSize);
    int indexZ = static_cast<int>((point.z - mainVoxel.minPoint.z) / voxelSize);

    return Vec3(indexX, indexY, indexZ);
}

void VoxelGrid::traverseRay(const Ray& ray) {
    // Compute the ray direction in voxel coordinates
    int stepX = (ray.direction.x >= 0) ? 1 : -1;
    int stepY = (ray.direction.y >= 0) ? 1 : -1;
    int stepZ = (ray.direction.z >= 0) ? 1 : -1;

    //Calculate initial intersection of the ray with the grid space
    Vec3 intersectionPoint(0, 0, 0);
    AABB_Face intersectionFace;

    bool intersect = mainVoxel.intersect(ray, intersectionPoint, intersectionFace);
    if (!intersect) return; //ray doesnt hit the gridspace, no need to walk it

    // Calculate the initial cell coordinates
    int currentX = static_cast<int>(intersex);
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

