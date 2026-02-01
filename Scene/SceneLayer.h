#pragma once

#include <RendererLayer.h>
#include <Layer.h>
#include <Camera.h>
#include <entt.hpp>  
#include <SystemManager.h>

class SceneLayer : public Layer
{
public:
	SceneLayer(RendererLayer* renderer);
	~SceneLayer();
	void onUpdate(float deltaTime) override;
	void onEvent(Event& e) override;

	inline entt::registry* getRegistry() { return &registry; }

private:
	entt::registry registry;
	RendererLayer* renderLayer;
	SystemManager systemManager;
	Camera camera;
};
