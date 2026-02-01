#pragma once

class Event;

class Layer {
public:
    virtual ~Layer() = default;

    virtual void onUpdate(float deltaTime) {}
    virtual void onEvent(Event& e) {}
};
