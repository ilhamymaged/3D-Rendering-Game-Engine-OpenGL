#pragma once
#include <glm.hpp>

class MouseInput 
{
public:
    struct MouseState
    {
        glm::vec2 position{ 0.0f };
        glm::vec2 delta{ 0.0f };
        glm::vec2 scroll{ 0.0f };
        bool firstMouse = true;
    };

    void update(glm::vec2 newPos, glm::vec2 scrollDelta);

    MouseState& getState() { return state; }
    const MouseState& getState() const { return state; }
    glm::vec2 getPosition() const { return state.position; }
    glm::vec2 getDelta() const { return state.delta; }

private:
    MouseState state;
    glm::vec2 lastPosition{ 0.0f };
};