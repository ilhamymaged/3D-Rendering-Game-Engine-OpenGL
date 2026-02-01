#include <PhysicsSystem.h>

void PhysicsSystem::update(entt::registry& registry, float dt) 
{
	auto view = registry.view<Rotator>();
	for(auto [e, r] : view.each())
	{
		if(r.enabled && registry.all_of<Sphere>(e))
		{
			auto& sphere = registry.get<Sphere>(e);
			float angle = r.speed * dt;
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::vec4 newCenter = rotation * glm::vec4(sphere.center, 1.0f);
			sphere.center = glm::vec3(newCenter);
		}
	}

}

void PhysicsSystem::onEvent(Event& e) 
{

}

