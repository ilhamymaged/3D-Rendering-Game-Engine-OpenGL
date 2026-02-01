#include <MeshRenderer.h>

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
	: mesh(mesh), material(material) {}

void MeshRenderer::render() const 
{
	material->bind();
	mesh->render();
}

void MeshRenderer::renderShadow() const
{
	mesh->render();
}
