#include "RenderSystem.h"
#include <ResourceManager.h>

RenderSystem::RenderSystem(RendererLayer* renderLayer, Camera& camera) :
    renderLayer{ renderLayer }, camera{ camera }
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::update(entt::registry& registry, float dt)
{
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
	std::vector<PointLight> pointLights;

    //Get Spheres
    auto spheresView = registry.view<Sphere>();
    for (auto [e, sphere] : spheresView.each())
        spheres.push_back(sphere);

    //Get Planes
    auto planeView = registry.view<Plane>();
    for (auto [e, plane] : planeView.each())
        planes.push_back(plane);

    auto pointLightView = registry.view<PointLight>();
    for (auto [e, light] : pointLightView.each())
        pointLights.push_back(light);

    RenderCommand cmd
    {
    .camera = camera,
    .spheres = spheres,
    .planes = planes,
    .pointLights = pointLights,
    };

    auto raySettingsView = registry.view<rayInfo>();
    for (auto [e, raySettings] : raySettingsView.each())
		cmd.raySettings = raySettings;

    renderLayer->submit(cmd);
}

void RenderSystem::onEvent(Event& e)
{
}
