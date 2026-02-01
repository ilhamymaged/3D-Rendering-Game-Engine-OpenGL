#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <Mesh.h>
#include <Texture.h>
#include <Shader.h>
#include <Model.h>

#include <assimp/scene.h>
#include <MeshRenderer.h>

class ResourceManager
{
public:
    ResourceManager() = delete;

    // --- Shaders ---
    static std::shared_ptr<Shader> loadShader(const std::string& name);
    static std::shared_ptr<Shader> getShader(const std::string& name);

    // --- Textures ---
    static std::shared_ptr<Texture> loadTexture(const std::string& path);
    static std::shared_ptr<Texture> getTexture(const std::string& name);

    // --- Models ---
    static std::shared_ptr<Model> loadModel(const std::string& path);
    static std::shared_ptr<Model> getModel(const std::string& name);

private:
    static std::shared_ptr<MeshRenderer> processMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);
    static std::string extractDirectory(const std::string& path);
private:
    static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    static std::unordered_map<std::string, std::shared_ptr<Model>> models;
};
