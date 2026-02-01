#pragma once
#include <System.h>
#include <glm.hpp>
#include <Components.h>

#define GRAVITY glm::vec3(0.0f, -9.81f, 0.0f)

class PhysicsSystem : public System
{
public:
    void update(entt::registry& registry, float dt) override;
    void onEvent(Event& e) override;

private:
    bool BoxCollision(BoxCollider& a, BoxCollider& b);
    bool TerrainBoxCollision(BoxCollider& b, TerrainCollider& t);
};
