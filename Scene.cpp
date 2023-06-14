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
    Vec3 bBoxminPoint = bBox.minPoint;  //point
    Vec3 bBoxmaxPoint = bBox.maxPoint;  //point

    Vec3 voxelSize = voxelGrid.getVoxelSize();
    Vec3 minVoxelIdx = voxelGrid.getVoxelArrayIndexes(bBoxminPoint);  //index of voxel that point is in
    Vec3 maxVoxelIdx = voxelGrid.getVoxelArrayIndexes(bBoxmaxPoint);  //index of voxel that point is in


    Vec3 tmp_min = voxelGrid.mainVoxel.minPoint + Vec3(FLT_EPSILON, FLT_EPSILON, FLT_EPSILON); //point
    Vec3 test_min = voxelGrid.getVoxelArrayIndexes(tmp_min); //index of voxel that point is in
    Vec3 tmp_max = voxelGrid.mainVoxel.maxPoint - Vec3(2*FLT_EPSILON, 2*FLT_EPSILON, 2*FLT_EPSILON); //point
    Vec3 test_max = voxelGrid.getVoxelArrayIndexes(tmp_max); //index of voxel that point is in


    Voxel *min_voxel = voxelGrid.getVoxel(test_min.x, test_min.y, test_min.z);
    Voxel* max_voxel = voxelGrid.getVoxel(test_max.x, test_max.y, test_max.z);

    // Iterate over the voxels within the bounding box
    for (int i = minVoxelIdx.x; i <= maxVoxelIdx.x; ++i) {
        for (int j = minVoxelIdx.y; j <= maxVoxelIdx.y; ++j) {
            for (int k = minVoxelIdx.z; k <= maxVoxelIdx.z; ++k) {
                Vec3 voxelMinPoint = voxelGrid.getVoxel(i, j, k)->minPoint;  //point
                Vec3 voxelMaxPoint = voxelGrid.getVoxel(i, j, k)->maxPoint;  //point

                if (bBoxminPoint.x < voxelMaxPoint.x && bBoxmaxPoint.x > voxelMinPoint.x &&
                    bBoxminPoint.y < voxelMaxPoint.y && bBoxmaxPoint.y > voxelMinPoint.y &&
                    bBoxminPoint.z < voxelMaxPoint.z && bBoxmaxPoint.z > voxelMinPoint.z) {
                    voxelGrid.getVoxel(i, j, k)->primitives.push_back(primitive);
                    voxelGrid.getVoxel(i, j, k)->occupied = true;
                }
            }
        }
    }
}
