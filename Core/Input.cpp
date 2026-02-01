#include <Input.h>

bool Input::ResetCameraMouse = false;
bool Input::keyStates[512];
bool Input::mouseStates[32];
float Input::mouseX = 0;
float Input::mouseY = 0;

bool Input::IsKeyDown(int key) { return keyStates[key]; }
bool Input::IsMouseDown(int b) { return mouseStates[b]; }

float Input::GetMouseX() {return mouseX;}

float Input::GetMouseY() {return mouseY;}

void Input::SetKey(int key, bool down) { keyStates[key] = down; }
void Input::SetMouse(int b, bool down) { mouseStates[b] = down; }
void Input::SetMousePos(float x, float y) { mouseX = x; mouseY = y; }

void Input::SetMode(GLenum mode, GLenum value)
{
	glfwSetInputMode(glfwGetCurrentContext(), mode, value);
}

GLenum Input::GetMode(GLenum mode)
{
	return glfwGetInputMode(glfwGetCurrentContext(), mode);
}

