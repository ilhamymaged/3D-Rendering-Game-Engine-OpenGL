#pragma once

#include <Camera.h>
#include <System.h>
#include <EventDispatcher.h>
#include <InputLayer.h>

class CameraSystem : public System
{   
public:
    CameraSystem(Camera& camera);
    void onEvent(Event& event) override;
    void update(entt::registry& registry, float dt) override;

private:
    Camera& camera;
};