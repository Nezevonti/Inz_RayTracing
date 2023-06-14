#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "voxelgrid.h"
#include "hittable.h"
#include "Camera.h"

class Scene {
public:
    Scene(const VoxelGrid& voxelGrid, const Camera& camera);

    void addPrimitive(Hittable* primitive);
    void addToVoxels(Hittable* primitive);
    
    void render();

private:
    VoxelGrid voxelGrid;
    Camera camera;
    std::vector<Hittable*> primitives;
};

#endif  // SCENE_H
