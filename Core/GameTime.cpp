#include "GameTime.h"
#include <GLFW/glfw3.h>

float GameTime::deltaTime = 0.0f;
float GameTime::lastTime = 0.0f;

void GameTime::Update()
{   
    float currentTime = (float)glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
}
