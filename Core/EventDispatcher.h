#pragma once
#include <Event.h>

class EventDispatcher 
{
public:
    EventDispatcher(Event& event)
        : event(event) {}

    template<typename T, typename F>
    bool dispatch(const F& func) {
        if (event.getEventType() == T::getStaticType()) {
            event.handled = func(*(T*)&event);
            return true;
        }
        return false;
    }

private:
    Event& event;
};
