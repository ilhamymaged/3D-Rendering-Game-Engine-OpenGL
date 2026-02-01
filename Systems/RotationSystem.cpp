#include "RotationSystem.h"

void RotationSystem::update(entt::registry& registry, float dt)
{
    //auto view = registry.view<Transform, Rotator>();
    //for (auto [entity, t, r] : view.each())
        //if (r.enabled)
            //t.rotation.y += r.speed * dt;
}

void RotationSystem::onEvent(Event& e)
{

}
