#pragma once
#include <memory>
#include <Mesh.h>
#include <Material.h>

class MeshRenderer 
{
public:
    MeshRenderer(std::shared_ptr<Mesh> mesh,
        std::shared_ptr<Material> material);

    std::shared_ptr<Mesh> getMesh() const { return mesh; }
    std::shared_ptr<Material> getMaterial() const { return material; }

    void render() const;
    void renderShadow() const;

private:
    std::shared_ptr<Mesh> mesh;     
    std::shared_ptr<Material> material;
};  
