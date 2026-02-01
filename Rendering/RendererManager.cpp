#include <ResourceManager.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <filesystem>
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Shader>> ResourceManager::shaders;
std::unordered_map<std::string, std::shared_ptr<Texture>> ResourceManager::textures;
std::unordered_map<std::string, std::shared_ptr<Model>> ResourceManager::models;

std::string ResourceManager::extractDirectory(const std::string& path)
{
    return std::filesystem::path(path).parent_path().string();
}


std::shared_ptr<Shader> ResourceManager::loadShader(const std::string& name)
{
    if (shaders.contains(name))
        return shaders[name];

    auto shader = std::make_shared<Shader>(name);
    shaders[name] = shader;
    return shader;
}

std::shared_ptr<Shader> ResourceManager::getShader(const std::string& name)
{
    if (!shaders.contains(name))
        return loadShader(name);

    return shaders[name];
}

std::shared_ptr<Texture> ResourceManager::loadTexture(const std::string& path)
{
    // Use only filename as key ("diffuse.png")
    std::string key = std::filesystem::path(path).filename().string();

    if (textures.contains(key))
        return textures[key];

    auto tex = std::make_shared<Texture>(path);
    textures[key] = tex;

    return tex;
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name)
{
    if (!textures.contains(name))
        return nullptr;
    return textures[name];
}


std::shared_ptr<Model> ResourceManager::getModel(const std::string& name)
{
    if (!models.contains(name))
        return nullptr;

    return models[name];
}


std::shared_ptr<Model> ResourceManager::loadModel(const std::string& path)
{
    if (models.contains(path))
        return models[path];

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_CalcTangentSpace
    );
    if (!scene || !scene->mRootNode)
    {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    auto model = std::make_shared<Model>(path);
    std::string directory = extractDirectory(path);

    glm::vec3 modelMin(FLT_MAX), modelMax(-FLT_MAX);

    std::function<void(aiNode*)> processNode;
    processNode = [&](aiNode* node)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            auto meshRenderer = processMesh(mesh, scene, directory);
            model->addMesh(meshRenderer);

            // Compute bounds for this mesh
            for (auto& vertex : meshRenderer->getMesh()->getVertices())
            {
                modelMin = glm::min(modelMin, vertex.position);
                modelMax = glm::max(modelMax, vertex.position);
            }
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
            processNode(node->mChildren[i]);
    };

    processNode(scene->mRootNode);

    model->size = modelMax - modelMin;
    model->center = (modelMax + modelMin) * 0.5f;

    models[path] = model;
    return model;
}

std::shared_ptr<MeshRenderer> ResourceManager::processMesh(
    aiMesh* mesh, const aiScene* scene, const std::string& directory)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
    {
        Vertex v;
        v.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        v.normal = mesh->HasNormals() ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)
            : glm::vec3(0.f, 1.f, 0.f);
        v.texCoords = mesh->mTextureCoords[0] ? glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)
            : glm::vec2(0.f);
        vertices.push_back(v);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            indices.push_back(mesh->mFaces[i].mIndices[j]);

    auto meshObj = std::make_shared<Mesh>(vertices, indices);

    std::shared_ptr<Texture> diffuseTex = nullptr;
    if (mesh->mMaterialIndex >= 0) 
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        aiString texPath;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS) {
            std::string fullPath = directory + "/" + texPath.C_Str();
            diffuseTex = loadTexture(fullPath);
        }
    }

    auto shader = ResourceManager::loadShader("default"); // your diffuse-only shader
    auto mat = std::make_shared<Material>(shader, diffuseTex);

    return std::make_shared<MeshRenderer>(meshObj, mat);
}