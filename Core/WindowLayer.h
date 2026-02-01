#pragma once
#include <Layer.h>
#include <GLFW/glfw3.h>
#include <string>
#include <queue>

class WindowLayer : public Layer {
public:
    WindowLayer(int width, int height, const std::string& title);
    ~WindowLayer();

    void onUpdate(float deltaTime) override;
	void onEvent(Event& e) override;

    bool shouldClose() const;
    void close();

    inline void pushEvent(Event* e) { eventQueue.push(e); }
    inline std::queue<Event*>& getEventQueue() { return eventQueue; }
    void clearEventQueue();

private:
    GLFWwindow* window;
    std::queue<Event*> eventQueue;
    bool cursorUnlocked = false;
};
