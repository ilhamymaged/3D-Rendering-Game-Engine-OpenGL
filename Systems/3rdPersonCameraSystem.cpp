#include "3rdPersonCameraSystem.h"
#include <Events.h>
#include <EventDispatcher.h>
#include <Input.h>

CameraSystem3rd::CameraSystem3rd(Camera& camera, entt::entity player)
    : camera(camera), player(player)
{
    distance = 10.0f; // desired distance behind the player
    verticalOffset = 2.0f; // height above player
}

void CameraSystem3rd::onEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowResizeEvent>([&](WindowResizeEvent& e) {
        camera.updateAspectRatio((float)e.getWidth() / e.getHeight());
        return true;
        });

    dispatcher.dispatch<MouseMovedEvent>([&](MouseMovedEvent& e) {
        if (Input::GetMode(CURSOR) == CURSOR_DISABLED && !InputLayer::WantImGuiCaptureMouse())
            camera.onMouseMove((float)e.getX(), (float)e.getY());
        return false;
        });

    dispatcher.dispatch<MouseScrolledEvent>([&](MouseScrolledEvent& e) {
        if (Input::GetMode(CURSOR) == CURSOR_DISABLED && !InputLayer::WantImGuiCaptureMouse())
            camera.onMouseScroll((float)e.getYOffset());
        return false;
        });
}

void CameraSystem3rd::update(entt::registry& registry, float dt)
{
    // Move the player with input
    if (InputLayer::WantImGuiCaptureKeyboard()) return;

    auto& playerTransform = registry.get<Transform>(player);

     float speed = 2.5f * dt;
     if (Input::IsKeyDown(W_KEY)) playerTransform.position += camera.getFront() * speed;
     if (Input::IsKeyDown(S_KEY)) playerTransform.position -= camera.getFront() * speed;
     if (Input::IsKeyDown(A_KEY)) playerTransform.position -= camera.getRight() * speed;
     if (Input::IsKeyDown(D_KEY)) playerTransform.position += camera.getRight() * speed;
     if (Input::IsKeyDown(SPACE_KEY)) playerTransform.position += glm::vec3(0.0f, 1.0f, 0.0f) * speed;

    // Update camera
    glm::vec3 offset(0.0f, verticalOffset, 0.0f);
    camera.recalcDirection(); 
    camera.setPosition(playerTransform.position - camera.getFront() * distance + offset);
}
