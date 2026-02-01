#pragma once
#include <memory>
#include <Shader.h>
#include <Texture.h>

enum class MaterialType 
{
    COLOR,
    TEXTURE
};

class Material 
{
public:
    Material(std::shared_ptr<Shader> shader,
        std::shared_ptr<Texture> diffuseTexture);

    Material(std::shared_ptr<Shader> shader,
        const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f)); 

    void bind() const;

    void setColor(const glm::vec3& c);
    void setTexture(std::shared_ptr<Texture> tex);

private:
    MaterialType type;
	glm::vec3 color;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> diffuseTexture;
};
