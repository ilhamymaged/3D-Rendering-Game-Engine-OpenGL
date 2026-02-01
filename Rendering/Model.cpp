#include <Model.h>	

Model::Model(const std::string& name)
{
	this->name = name;
}

std::vector<std::shared_ptr<MeshRenderer>>& Model::getMehes()
{
    return meshes;
}

void Model::addMesh(std::shared_ptr<MeshRenderer> mesh)
{
    meshes.push_back(mesh);
}

void Model::renderShadow()
{
    for (auto& mesh : meshes)
        mesh->renderShadow();
}

void Model::render()
{
    for (auto& mesh : meshes) 
        mesh->render();
}
