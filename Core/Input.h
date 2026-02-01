#pragma once

#include <GLFW/glfw3.h>

#define A_KEY GLFW_KEY_A
#define D_KEY GLFW_KEY_D
#define W_KEY GLFW_KEY_W
#define S_KEY GLFW_KEY_S
#define SPACE_KEY GLFW_KEY_SPACE
#define ESCAPE_KEY GLFW_KEY_ESCAPE
#define LEFT_CTRL_KEY GLFW_KEY_LEFT_CONTROL

#define CURSOR_DISABLED GLFW_CURSOR_DISABLED
#define CURSOR_NORMAL GLFW_CURSOR_NORMAL
#define CURSOR GLFW_CURSOR

class Input
{
public:
    static bool IsKeyDown(int key);
    static bool IsMouseDown(int button);
    static float GetMouseX();   
    static float GetMouseY();

    static void SetKey(int key, bool down);
    static void SetMouse(int button, bool down);
    static void SetMousePos(float x, float y);

    static void SetMode(GLenum mode, GLenum value);
    static GLenum GetMode(GLenum mode);

    static bool ResetCameraMouse;

private:
    static bool keyStates[512];
    static bool mouseStates[32];
    static float mouseX, mouseY;
};
