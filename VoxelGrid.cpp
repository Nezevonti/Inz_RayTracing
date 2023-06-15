#include "voxelgrid.h"

// Include the Voxel class header
#include "voxel.h"

#include <iostream>

// VoxelGrid constructor implementation
VoxelGrid::VoxelGrid(int sizeX, int sizeY, int sizeZ)
    : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {

    int numVoxels = sizeX * sizeY * sizeZ;
    
    for (int i = 0; i < numVoxels; i++) {
        voxels.push_back(new Voxel());
    }

    mainVoxel = Voxel(Vec3(0, 0, 0), Vec3(sizeX, sizeY, sizeZ), 1.0);
    calculateVoxelBounds();
}

VoxelGrid::VoxelGrid(int sizeX, int sizeY, int sizeZ, Vec3 minPoint, Vec3 maxPoint) 
    : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {

        int numVoxels = sizeX * sizeY * sizeZ;

        for (int i = 0; i < numVoxels; i++) {
            voxels.push_back(new Voxel());
        }

        mainVoxel =  Voxel(minPoint, maxPoint, 1.0);
        calculateVoxelBounds();

}

// VoxelGrid destructor implementation
VoxelGrid::~VoxelGrid() {
    for (auto p : voxels) {
        delete p;
    }
    voxels.clear();
}

bool VoxelGrid::isPointInsideVoxel(const Vec3& point, const Vec3& voxelMin, const Vec3& voxelMax) const{
    return point.x >= voxelMin.x && point.x <= voxelMax.x &&
        point.y >= voxelMin.y && point.y <= voxelMax.y &&
        point.z >= voxelMin.z && point.z <= voxelMax.z;
}

Vec3 VoxelGrid::getVoxelSize() const {
    float voxelSizeX = (mainVoxel.maxPoint.x - mainVoxel.minPoint.x) / sizeX;
    float voxelSizeY = (mainVoxel.maxPoint.y - mainVoxel.minPoint.y) / sizeY;
    float voxelSizeZ = (mainVoxel.maxPoint.z - mainVoxel.minPoint.z) / sizeZ;

    return Vec3(voxelSizeX, voxelSizeY, voxelSizeZ);
}

Vec3 VoxelGrid::getVoxelArrayIndexes(const Vec3& point) const {

    //I had i there for a reason, im gonna comment it out but keep the code snippet
    // Check if the point is inside the main AABB
    //if (!isPointInsideVoxel(point, mainVoxel.minPoint, mainVoxel.maxPoint)) {
        //throw std::out_of_range("Vec3 index out of range");
    //}

    Vec3 voxelSize = getVoxelSize();

    int indexX = static_cast<int>((point.x - mainVoxel.minPoint.x) / voxelSize.x);
    int indexY = static_cast<int>((point.y - mainVoxel.minPoint.y) / voxelSize.y);
    int indexZ = static_cast<int>((point.z - mainVoxel.minPoint.z) / voxelSize.z);

    // Check if the point is on the edge or corner of the voxel grid
    if (indexX == sizeX || indexY == sizeY || indexZ == sizeZ) {
        // Check if the point does not belong to the edge/corner
        if (point.x <= mainVoxel.maxPoint.x || point.y <= mainVoxel.maxPoint.y || point.z <= mainVoxel.maxPoint.z) {
            // Adjust the indexes to the maximum valid value
            if (indexX == sizeX) indexX--;
            if (indexY == sizeY) indexY--;
            if (indexZ == sizeZ) indexZ--;
        }
        else {
            throw std::out_of_range("Vec3 index out of range");
        }
    }

    return Vec3(indexX, indexY, indexZ);
}

void VoxelGrid::traverseRay(const Ray& ray, HitRecord& record) {
    // Compute the ray direction in voxel coordinates
    int stepX = (ray.direction.x >= 0) ? 1 : -1;
    int stepY = (ray.direction.y >= 0) ? 1 : -1;
    int stepZ = (ray.direction.z >= 0) ? 1 : -1;

    //Calculate initial intersection of the ray with the grid space
    Vec3 intersectionPoint(0, 0, 0);
    AABB_Face intersectionFace;

    float tmin_overall = -INFINITY;
    float tmax_overall = INFINITY;

    bool intersect = mainVoxel.intersect(ray, intersectionPoint, intersectionFace);
    if (!intersect) return; //ray doesnt hit the gridspace, no need to walk it

    //check 

    // Calculate the initial cell coordinates
    Vec3 currentVoxelIndexes = getVoxelArrayIndexes(intersectionPoint);
    int currentX = currentVoxelIndexes.x;
    int currentY = currentVoxelIndexes.y;
    int currentZ = currentVoxelIndexes.z;

    // Calculate the tDelta values
    float tDeltaX = std::abs(1.0f / ray.direction.x);
    float tDeltaY = std::abs(1.0f / ray.direction.y);
    float tDeltaZ = std::abs(1.0f / ray.direction.z);

    // Calculate the tMax values
    float tMaxX = tDeltaX * 0.5f;
    float tMaxY = tDeltaY * 0.5f;
    float tMaxZ = tDeltaZ * 0.5f;

    Voxel* currentVoxel;

    // Perform the voxel traversal loop
    while (currentX >= 0 && currentX < sizeX &&
        currentY >= 0 && currentY < sizeY &&
        currentZ >= 0 && currentZ < sizeZ) {
        // Process the current cell


        currentVoxel = getVoxel(currentX, currentY, currentZ);
        tmin_overall = -INFINITY;
        tmax_overall = INFINITY;

        if (currentVoxel->occupied) {
            int numPrimitives = currentVoxel->primitives.size();

            for (int i = 0; i < numPrimitives; i++) {

                //there is a primitive in this voxel, does the ray intersect with its aabb?
                bool hit_prim_aabb = currentVoxel->primitives.at(i)->boundingBox.intersect(ray, intersectionPoint, intersectionFace,tmin_overall,tmax_overall);

                if (hit_prim_aabb) {
                    //get t_min & t_max for given ray and voxel?
                    bool hit_prim = currentVoxel->primitives.at(i)->hit(ray, tmin_overall, tmax_overall, record);

                    if (hit_prim) {
                        return;
                    }
                }                                
            }
        }

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

        // Update the ray parameter (t) 
        //currentVoxelIndexes.x = currentX;
        //currentVoxelIndexes.y = currentY;
        //currentVoxelIndexes.z = currentZ;
        //currentVoxel.print();

        // Check for intersection or termination conditions

        // Repeat the loop
    }
}

Voxel* VoxelGrid::getVoxel(int x, int y, int z) {
    int index = x + y * sizeX + z * sizeX * sizeY;
    return voxels.at(index);
}


void VoxelGrid::calculateVoxelBounds() {
    Vec3 voxelSize = getVoxelSize();

    for (int z = 0; z < sizeZ; ++z) {
        for (int y = 0; y < sizeY; ++y) {
            for (int x = 0; x < sizeX; ++x) {
                int index = z * sizeX * sizeY + y * sizeX + x;
                Voxel* voxel = voxels.at(index);


                voxel->minPoint = Vec3(x * voxelSize.x + mainVoxel.minPoint.x, y * voxelSize.y + mainVoxel.minPoint.y, z * voxelSize.z + mainVoxel.minPoint.z);
                voxel->maxPoint = voxel->minPoint + voxelSize;
            }
        }
    }
}

