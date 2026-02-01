#pragma once
#include "Layer.h"

class GameTime
{
public:
    static void Update();
    static float DeltaTime() { return deltaTime; }

private:
    static float lastTime;
    static float deltaTime;
}; 