#include <Terrain/Terrain.h>
#include <cmath>
#include <ResourceManager.h>
#include <Terrain/PerlinNoise.hpp>

Terrain::Terrain(int width, int depth, float scale)
    : width(width), depth(depth), scale(scale)
{
    generateHeightMap();
    generateMesh();
}

void Terrain::generateHeightMap()
{
    //const float heightMultiplier = 10.0f; 
    //const float frequency = 0.05f;
    //const int octaves = 6;

    //siv::PerlinNoise perlin{ 123456u }; 

    heightMap.resize(width * depth);
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            //float noise = perlin.octave2D_01(x * frequency, z * frequency, octaves);
            //heightMap[z * width + x] = noise * heightMultiplier;
            heightMap[z * width + x] = 0.0f;
        }
    }
}

float Terrain::getHeightAt(float worldX, float worldZ) const
{
    // Convert world coordinates to terrain grid coordinates
    float terrainX = worldX / scale;
    float terrainZ = worldZ / scale;

    int x0 = static_cast<int>(floor(terrainX));
    int z0 = static_cast<int>(floor(terrainZ));
    int x1 = x0 + 1;
    int z1 = z0 + 1;

    // Clamp to terrain boundaries
    x0 = glm::clamp(x0, 0, width - 1);
    z0 = glm::clamp(z0, 0, depth - 1);
    x1 = glm::clamp(x1, 0, width - 1);
    z1 = glm::clamp(z1, 0, depth - 1);

    // Get heights of four surrounding vertices
    float h00 = heightMap[z0 * width + x0];
    float h10 = heightMap[z0 * width + x1];
    float h01 = heightMap[z1 * width + x0];
    float h11 = heightMap[z1 * width + x1];

    // Fractional distances
    float fx = terrainX - x0;
    float fz = terrainZ - z0;

    // Bilinear interpolation
    float h0 = glm::mix(h00, h10, fx);
    float h1 = glm::mix(h01, h11, fx);
    float height = glm::mix(h0, h1, fz);

    return height;
}

glm::vec3 Terrain::calculateNormal(int x, int z) const
{
    // finite difference approximation
    float hL = (x > 0) ? heightMap[z * width + (x - 1)] : heightMap[z * width + x];
    float hR = (x < width - 1) ? heightMap[z * width + (x + 1)] : heightMap[z * width + x];
    float hD = (z > 0) ? heightMap[(z - 1) * width + x] : heightMap[z * width + x];
    float hU = (z < depth - 1) ? heightMap[(z + 1) * width + x] : heightMap[z * width + x];

    glm::vec3 normal = glm::vec3(hL - hR, 2.0f, hD - hU);
    return glm::normalize(normal);
}

void Terrain::generateMesh()
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int z = 0; z < depth; z++)
    {
        for (int x = 0; x < width; x++)
        {
            Vertex v;
            v.position = glm::vec3(x * scale, heightMap[z * width + x], z * scale);
            v.normal = calculateNormal(x, z);
            v.texCoords = glm::vec2((float)x / width, (float)z / depth);
            vertices.push_back(v);
        }
    }

    for (int z = 0; z < depth - 1; z++)
    {
        for (int x = 0; x < width - 1; x++)
        {
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;

            // first triangle
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            // second triangle
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
    auto mesh = std::make_shared<Mesh>(vertices, indices);
    auto material = std::make_shared<Material>(
        ResourceManager::loadShader("default"),
		glm::vec3(0.3f, 0.4f, 0.3f)
	);
    meshRenderer = std::make_shared<MeshRenderer>(mesh, material);

    terrainModel = std::make_shared<Model>("Terrain");
    terrainModel->addMesh(meshRenderer);
}

