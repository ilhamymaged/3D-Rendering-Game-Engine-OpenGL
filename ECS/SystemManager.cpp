#include <SystemManager.h>	

void SystemManager::update(entt::registry& registry, float dt) 
{
    for (auto& s : systems) s->update(registry, dt);
}

void SystemManager::fireEvents(Event& event)    
{
    for (auto& s : systems) s->onEvent(event);
}
