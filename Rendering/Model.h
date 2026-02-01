#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <Shader.h>
#include <MeshRenderer.h>

class Model
{
public:
    Model(const std::string& name);

    std::vector<std::shared_ptr<MeshRenderer>>& getMehes();
    void addMesh(std::shared_ptr<MeshRenderer> mesh);
    void render();
    void renderShadow();
private:
    std::vector<std::shared_ptr<MeshRenderer>> meshes;
    std::string name;

public: 
    glm::vec3 size;
    glm::vec3 center;
};