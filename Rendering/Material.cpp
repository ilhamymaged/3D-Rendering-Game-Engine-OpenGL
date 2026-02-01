#include <Material.h>
   

Material::Material(std::shared_ptr<Shader> shader,
    std::shared_ptr<Texture> diffuseTexture)
    : shader(shader), diffuseTexture(diffuseTexture), type{ MaterialType::TEXTURE }, color{ 1.0f, 1.0f, 1.0f }
{}

Material::Material(std::shared_ptr<Shader> shader,
    const glm::vec3& color)
    : shader(shader), color(color), type{ MaterialType::COLOR }
{}

void Material::bind() const 
{
    shader->use();
    shader->setInt((int)type, "materialType");

    if (type == MaterialType::COLOR)
    {
        shader->setVec3(color, "color");
    }

    if (type == MaterialType::TEXTURE && diffuseTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        diffuseTexture->bind();
        shader->setInt(0, "diffuseTexture");
    }
}

void Material::setColor(const glm::vec3& c)
{
    color = c;
    type = MaterialType::COLOR;
}

void Material::setTexture(std::shared_ptr<Texture> tex)
{
    diffuseTexture = tex;
    type = MaterialType::TEXTURE;
}
