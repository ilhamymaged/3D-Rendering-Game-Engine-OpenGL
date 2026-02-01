#pragma once
#include <Event.h>

class WindowResizeEvent : public Event 
{
public:
    WindowResizeEvent(int w, int h)
        : width(w), height(h) {
    }

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
    int width, height;
};

class WindowCloseEvent : public Event 
{
public:
    WindowCloseEvent() {}

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class KeyPressedEvent : public Event 
{
public:
    KeyPressedEvent(int key, int repeat)
        : keyCode(key), repeatCount(repeat) {}

    inline int getKeyCode() const { return keyCode; }
    inline int getRepeatCount() const { return repeatCount; }

    EVENT_CLASS_TYPE(KeyPressed)
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

private:
    int keyCode;
    int repeatCount;
};

class KeyReleasedEvent : public Event 
{
public:
    KeyReleasedEvent(int key)
        : keyCode(key) {}

    int getKeyCode() const { return keyCode; }

    EVENT_CLASS_TYPE(KeyReleased)
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

private:
    int keyCode;
};

class MouseMovedEvent : public Event 
{
public:
    MouseMovedEvent(double x, double y)
        : mouseX(x), mouseY(y) {
    }

    double getX() const { return mouseX; }
    double getY() const { return mouseY; }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    double mouseX, mouseY;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(double xOffset, double yOffset)
        : xOffset(xOffset), yOffset(yOffset) {}

    double getXOffset() const { return xOffset; }
    double getYOffset() const { return yOffset; }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)   

private:
	double xOffset, yOffset;
};
