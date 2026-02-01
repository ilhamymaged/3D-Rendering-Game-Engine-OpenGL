#pragma once

#include <Camera.h>
#include <System.h>
#include <EventDispatcher.h>
#include <InputLayer.h>
#include <Components.h>

class CameraSystem3rd : public System
{
public:
    CameraSystem3rd(Camera& camera, entt::entity player);
    void onEvent(Event& event) override;
    void update(entt::registry& registry, float dt) override;

private:
    Camera& camera;
    entt::entity player;
    float distance;
    float verticalOffset;   
};