#include <entt.hpp>
#include <System.h>
#include <Components.h>

class RotationSystem : public System
{
public:
    void update(entt::registry& registry, float dt) override;
    void onEvent(Event& e) override;
};