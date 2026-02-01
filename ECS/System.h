#pragma once
#include <entt.hpp>
#include <Event.h>

class System 
{
public:
    virtual void update(entt::registry& registry, float dt) = 0;
    virtual void onEvent(Event& e) = 0;
    virtual ~System() = default;
};
