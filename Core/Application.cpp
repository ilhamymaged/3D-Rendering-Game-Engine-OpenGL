#include <Application.h>
#include <WindowLayer.h>
#include <GameTime.h>
#include <SceneLayer.h>
#include <Event.h>
#include <InputLayer.h>
#include <RendererLayer.h>
#include <UILayer.h>

Application::Application(const std::string& title, int width, int height) 
{
    windowLayer = new WindowLayer(width, height, title);
	rendererLayer = new RendererLayer(width, height);
	inputLayer = new InputLayer();
	sceneLayer = new SceneLayer(rendererLayer); 
    _UILayer = new UILayer(sceneLayer->getRegistry());

    pushLayer(windowLayer);
    pushLayer(inputLayer);
    pushLayer(rendererLayer);
    pushLayer(sceneLayer);
    pushLayer(_UILayer);
}

Application::~Application()
{
    for (auto& layer : layers) delete layer;
}

void Application::pushLayer(Layer* layer) 
{
    layers.push_back(layer);
}

void Application::run() 
{
    while (!windowLayer->shouldClose()) 
    {
        GameTime::Update();

        auto& queue = windowLayer->getEventQueue();
        while (!queue.empty())
        {
            Event* e = queue.front();
            queue.pop();

            for (auto it = layers.rbegin(); it != layers.rend(); ++it)
            {   
                (*it)->onEvent(*e);
                if (e->handled) break; 
            }

            delete e;
        }

        windowLayer->clearEventQueue();
        for (auto& layer : layers) layer->onUpdate(GameTime::DeltaTime());
    }
}
