#pragma once
#define GLFW_INCLUDE_NONE
#include <vector>
#include <string>
#include <Layer.h>

class WindowLayer;
class RendererLayer;
class SceneLayer;
class InputLayer;
class UILayer;

class Application 
{
public:
    Application(const std::string& title, int width, int height);
    ~Application();

    virtual void run();
    virtual void pushLayer(Layer* layer); 

private:
    std::vector<Layer*> layers;

    WindowLayer* windowLayer;
	RendererLayer* rendererLayer;
	SceneLayer* sceneLayer;
	InputLayer* inputLayer;
    UILayer* _UILayer;
};

