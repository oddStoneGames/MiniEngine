#ifndef WINDOW_EVENTS_H
#define WINDOW_EVENTS_H

#include "Event.h"

namespace MiniEngine
{
    enum class WindowEvents
    {
        WindowResize,
        WindowClose
    };

    class WindowResizeEvent : public Event<WindowEvents>
    {
    public:
        WindowResizeEvent() : Event<WindowEvents>(WindowEvents::WindowResize, "WindowResize") {}
        virtual ~WindowResizeEvent() {}
        int width = 0, height = 0;  // New Width & Height.
    };

    class WindowCloseEvent : public Event<WindowEvents>
    {
    public:
        WindowCloseEvent() : Event<WindowEvents>(WindowEvents::WindowClose, "WindowClose") {}
        virtual ~WindowCloseEvent() {}
    };
}

#endif // !WINDOW_EVENTS_H