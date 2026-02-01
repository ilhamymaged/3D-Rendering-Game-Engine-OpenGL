#include "CameraSystem.h"
#include <Events.h>
#include <EventDispatcher.h>
#include <Input.h>

CameraSystem::CameraSystem(Camera& camera) : camera(camera) {}

void CameraSystem::onEvent(Event& event)
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

    dispatcher.dispatch<MouseScrolledEvent >([&](MouseScrolledEvent& e) {
        if (Input::GetMode(CURSOR) == CURSOR_DISABLED && !InputLayer::WantImGuiCaptureMouse())
            camera.onMouseScroll((float)e.getYOffset());
        return false;
        });
}

void CameraSystem::update(entt::registry& registry, float dt)
{
    if (InputLayer::WantImGuiCaptureKeyboard()) return;

    float speed = camera.speed * dt;
    if (Input::IsKeyDown(W_KEY)) camera.moveForward(speed); 
    if (Input::IsKeyDown(S_KEY)) camera.moveBackward(speed);
    if (Input::IsKeyDown(A_KEY)) camera.moveLeft(speed);
    if (Input::IsKeyDown(D_KEY)) camera.moveRight(speed);
    if (Input::IsKeyDown(SPACE_KEY)) camera.moveUp(speed);
}
