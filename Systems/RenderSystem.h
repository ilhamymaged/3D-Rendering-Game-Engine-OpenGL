#pragma once

#include <System.h>
#include <RendererLayer.h>
#include <ResourceManager.h>
#include <Lights.h>
#include <Camera.h>
#include <Components.h> 

class RenderSystem : public System
{
public:
    RenderSystem(RendererLayer* renderLayer, Camera& camera);
    ~RenderSystem();

	void update(entt::registry& registry, float dt) override;
    void onEvent(Event& e) override;

private:
    RendererLayer* renderLayer;
    Camera& camera;
};

