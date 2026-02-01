#pragma once
#include <Layer.h>
#include <entt.hpp>

class UILayer : public Layer
{
public:
	UILayer(entt::registry* registry);
	~UILayer();

	void onUpdate(float deltaTime) override;
	void onEvent(Event& e) override;

private:
	entt::registry* registry = nullptr;
	entt::entity selectedEntity = entt::null;
	entt::entity newEntity = entt::null;

	void drawHierarchy();
	void drawInspector();
};