#pragma once
#include <vector>
#include <memory>
#include <glm.hpp>
#include <Model.h>

class Terrain
{
public:
    Terrain(int width, int depth, float scale);

    void generateHeightMap();
    void generateMesh();
    float getHeightAt(float worldX, float worldZ) const;

    std::shared_ptr<Model> getModel() const { return terrainModel; }

    int width, depth;
    float scale;
private:
    std::vector<float> heightMap;
    std::shared_ptr<MeshRenderer> meshRenderer;
    std::shared_ptr<Model> terrainModel;  
    glm::vec3 calculateNormal(int x, int z) const;
};
