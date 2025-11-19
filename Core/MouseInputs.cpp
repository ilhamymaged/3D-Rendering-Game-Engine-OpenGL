#include <MouseInputs.h>
#include <GLFW/glfw3.h>

void MouseInput::update(glm::vec2 newPos, glm::vec2 scrollDelta) 
{
    if (state.firstMouse)
    {
        lastPosition = newPos;
        state.firstMouse = false;
    }

    state.delta = newPos - lastPosition;
    lastPosition = newPos;
    state.position = newPos;
    state.scroll = scrollDelta;
}

