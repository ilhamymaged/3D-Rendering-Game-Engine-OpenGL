#pragma once
#include <Layer.h>
#include <MouseInputs.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

class WindowLayer;

class InputLayer : public Layer {
public:
    InputLayer(WindowLayer* windowLayer);

    void onUpdate(float deltaTime) override;
    void onAttach() override;
    bool isKeyPressed(int key) const;

	inline const MouseInput& getMouse() const { return mouse; }

private:
    WindowLayer* window;
    std::unordered_map<int, bool> keyState;
    MouseInput mouse;

    static void mouseCallback(GLFWwindow* win, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* win, double xoffset, double yoffset);
};

#define W_KEY GLFW_KEY_W
#define A_KEY GLFW_KEY_A
#define S_KEY GLFW_KEY_S
#define D_KEY GLFW_KEY_D
#define SPACE_KEY GLFW_KEY_SPACE
