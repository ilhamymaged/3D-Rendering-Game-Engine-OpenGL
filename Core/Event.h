#pragma once
#include <string>
#include <functional>

enum class EventType 
{
    None = 0,
    WindowResize,
    WindowClose,
    KeyPressed,
    KeyReleased,
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
	MouseScrolled
};

enum EventCategory 
{
    None = 0,
    EventCategoryApplication = 1 << 0,
    EventCategoryInput = 1 << 1,
    EventCategoryKeyboard = 1 << 2,
    EventCategoryMouse = 1 << 3,
    EventCategoryMouseButton = 1 << 4
};

#define EVENT_CLASS_TYPE(type) \
    static EventType getStaticType() { return EventType::##type; } \
    EventType getEventType() const override { return getStaticType(); } \
    const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    int getCategoryFlags() const override { return category; }

class Event 
{
public:
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual int getCategoryFlags() const = 0;

    bool handled = false;
    bool isInCategory(EventCategory category) 
    {
        return getCategoryFlags() & category;
    }
};
