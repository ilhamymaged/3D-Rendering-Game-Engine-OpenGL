#include "InputLayer.h"
#include "WindowLayer.h"
#include <iostream>

InputLayer::InputLayer(WindowLayer* windowLayer)
    : window(windowLayer) 
{
}

void InputLayer::onUpdate(float deltaTime) 
{
    keyState.clear();
    GLFWwindow* win = window->getWindow();

    for (int key = 32; key <= 348; ++key) {
        keyState[key] = (glfwGetKey(win, key) == GLFW_PRESS);
    }

    if(isKeyPressed(GLFW_KEY_ESCAPE))
		window->close();
}

void InputLayer::onAttach()
{
    GLFWwindow* win = window->getWindow();
    glfwSetWindowUserPointer(win, this);
    glfwSetCursorPosCallback(win, mouseCallback);
    glfwSetScrollCallback(win, scrollCallback);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputLayer::mouseCallback(GLFWwindow* win, double xpos, double ypos) {
    InputLayer* self = (InputLayer*)glfwGetWindowUserPointer(win);

    glm::vec2 pos(xpos, ypos);
    self->mouse.update(pos, glm::vec2(0));
}


void InputLayer::scrollCallback(GLFWwindow* win, double xoffset, double yoffset) 
{
    InputLayer* self = (InputLayer*)glfwGetWindowUserPointer(win);
    if (!self) return;

    glm::vec2 pos = self->mouse.getPosition();
    self->mouse.update(pos, glm::vec2(xoffset, yoffset));
}

bool InputLayer::isKeyPressed(int key) const 
{
    auto it = keyState.find(key);
    if (it != keyState.end())
        return it->second;
    return false;
}
