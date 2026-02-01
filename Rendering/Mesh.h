#pragma once
#include <iostream>
#include <vector>
#include <Shader.h>
#include <Texture.h>
#include <assimp/material.h>

struct quadVertex
{
    glm::vec2 position;
};

struct Vertex 
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh 
{
public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices);

    ~Mesh();
    void render() const;

    inline std::vector<Vertex>& getVertices() { return vertices; }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;
};