#include "scene.h"
#include <limits>

Scene::Scene(const VoxelGrid& voxelGrid, const Camera& camera)
    : voxelGrid(voxelGrid), camera(camera)
{

}


void Scene::render() {
    camera.draw(voxelGrid);
}


void Scene::addPrimitive(Hittable* primitive) {
    primitives.push_back(primitive);
    addToVoxels(primitive);
}

void Scene::addToVoxels(Hittable* primitive) {
    const AABB& bBox = primitive->boundingBox;
    Vec3 bBoxminPoint = bBox.minPoint;
    Vec3 bBoxmaxPoint = bBox.maxPoint;

    Vec3 voxelSize = voxelGrid.getVoxelSize();
    Vec3 minVoxelIdx = voxelGrid.getVoxelArrayIndexes(bBoxminPoint);
    Vec3 maxVoxelIdx = voxelGrid.getVoxelArrayIndexes(bBoxmaxPoint);

    // Iterate over the voxels within the bounding box
    for (int i = minVoxelIdx.x; i <= maxVoxelIdx.x; ++i) {
        for (int j = minVoxelIdx.y; j <= maxVoxelIdx.y; ++j) {
            for (int k = minVoxelIdx.z; k <= maxVoxelIdx.z; ++k) {
                Vec3 voxelMinPoint = voxelGrid.getVoxel(i, j, k).minPoint;
                Vec3 voxelMaxPoint = voxelGrid.getVoxel(i, j, k).maxPoint;

                if (bBoxminPoint.x < voxelMaxPoint.x && bBoxmaxPoint.x > voxelMinPoint.x &&
                    bBoxminPoint.y < voxelMaxPoint.y && bBoxmaxPoint.y > voxelMinPoint.y &&
                    bBoxminPoint.z < voxelMaxPoint.z && bBoxmaxPoint.z > voxelMinPoint.z) {
                    voxelGrid.getVoxel(i, j, k).primitives.push_back(primitive);
                    voxelGrid.getVoxel(i, j, k).occupied = true;
                }
            }
        }
    }
}
