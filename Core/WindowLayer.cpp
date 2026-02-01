#include "WindowLayer.h"
#include <Events.h>
#include <EventDispatcher.h>
#include <iostream>
#include <Input.h>

WindowLayer::WindowLayer(int w, int h, const std::string& t)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w, h, t.c_str(), nullptr, nullptr);
    if (!window) 
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(0);

    //set The Events
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height) {
        WindowLayer* layer = (WindowLayer*)glfwGetWindowUserPointer(win);
        layer->pushEvent(new WindowResizeEvent(width, height));
    });

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
        WindowLayer* layer = (WindowLayer*)glfwGetWindowUserPointer(win);

        if (action == GLFW_PRESS)
            layer->pushEvent(new KeyPressedEvent(key, 0));
        else if (action == GLFW_REPEAT)
            layer->pushEvent(new KeyPressedEvent(key, 1));
        else if (action == GLFW_RELEASE)
            layer->pushEvent(new KeyReleasedEvent(key));
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
		WindowLayer* layer = (WindowLayer*)glfwGetWindowUserPointer(window);
		layer->pushEvent(new MouseScrolledEvent(xOffset, yOffset));
	});

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowLayer* layer = (WindowLayer*)glfwGetWindowUserPointer(window);
        layer->pushEvent(new MouseMovedEvent(xPos, yPos));
    });
}

WindowLayer::~WindowLayer() 
{
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void WindowLayer::onUpdate(float dt) 
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void WindowLayer::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<KeyPressedEvent>([&](KeyPressedEvent& event) {
        if (Input::IsKeyDown(LEFT_CTRL_KEY))
        {
            cursorUnlocked = !cursorUnlocked;
            glfwSetInputMode(window,
                GLFW_CURSOR,
                cursorUnlocked ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED
            );
        }

        if (!cursorUnlocked) 
            Input::ResetCameraMouse = true;   

        if (Input::IsKeyDown(ESCAPE_KEY)) close();
        return true; 
	});

}

bool WindowLayer::shouldClose() const { return glfwWindowShouldClose(window); }
void WindowLayer::close() { glfwSetWindowShouldClose(window, GLFW_TRUE); }

void WindowLayer::clearEventQueue()
{
    while (!eventQueue.empty())
    {
        delete eventQueue.front();
        eventQueue.pop();
    }
}
