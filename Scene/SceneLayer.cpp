#include <SceneLayer.h>
#include <Components.h>
#include <Events.h>
#include <EventDispatcher.h>
#include <Input.h>
#include <ResourceManager.h>
#include <Terrain/Terrain.h>
#include <InputLayer.h>
#include <CameraSystem.h>
#include <RotationSystem.h>
#include <RenderSystem.h>
#include <PhysicsSystem.h>
#include <3rdPersonCameraSystem.h>

SceneLayer::SceneLayer(RendererLayer* renderer)
    :renderLayer{ renderer }, camera{renderLayer->windowWidth, renderLayer->windowHeight}
{
    systemManager.addSystem<CameraSystem>(camera);
    systemManager.addSystem<RenderSystem>(renderer, camera);
	systemManager.addSystem<RotationSystem>();

    auto cameraEntity = registry.create();
    registry.emplace<CameraComponent>(cameraEntity, camera);

    auto ray = registry.create();
	registry.emplace<rayInfo>(ray, 3);

    auto pointLight = registry.create();
    registry.emplace<PointLight>(pointLight,
        glm::vec3(2.0f, 5.0f, 3.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.1f, 0.1f, 0.1f)
	);
	registry.emplace<Rotator>(pointLight, true);

    auto sphereEntity = registry.create();
    registry.emplace<Sphere>(sphereEntity,
            glm::vec3(0.0f),
            0.5f,
		    0.5f,
            glm::vec3(1.0f, 0.0f, 1.0f)
    );
    registry.emplace<Rotator>(sphereEntity, true);

    auto planeEntity = registry.create();
    registry.emplace<Plane>(planeEntity,
        Plane
        {
            .normal = glm::vec3(0.0f, 1.0f, 0.0f),
            .color = glm::vec3(1.0f, 1.0f, 1.0f),
            .point = glm::vec3(0.0f, -0.5f, 0.0f),
			.reflectivity = 0.0f
        });
	//registry.emplace<Rotator>(planeEntity, false);
}

SceneLayer::~SceneLayer() = default;

void SceneLayer::onUpdate(float dt)
{
    systemManager.update(registry, dt);
}

void SceneLayer::onEvent(Event& event)
{
    systemManager.fireEvents(event);
}

