#ifndef MOUSE_EVENTS_H
#define MOUSE_EVENTS_H

#include "Event.h"

namespace MiniEngine
{
    enum class MouseEvents
    {
        MouseMoved,
        MouseButtonDown,
        MouseButtonUp
    };

    class MouseMovedEvent : public Event<MouseEvents>
    {
    public:
        MouseMovedEvent() : Event<MouseEvents>(MouseEvents::MouseMoved, "MouseMoved") {}
        virtual ~MouseMovedEvent() {}
        int x = -1, y = -1;   // New Mouse Position in screen coordinates under the current window.
    };

    class MouseButtonDownEvent : public Event<MouseEvents>
    {
    public:
        MouseButtonDownEvent() : Event<MouseEvents>(MouseEvents::MouseButtonDown, "MouseButtonDown") {}
        virtual ~MouseButtonDownEvent() {}
        int button = -1; // Mouse Button that was Down, 1 - LMB, 2 - MMB, 3 - RMB
    };

    class MouseButtonUpEvent : public Event<MouseEvents>
    {
    public:
        MouseButtonUpEvent() : Event<MouseEvents>(MouseEvents::MouseButtonUp, "MouseButtonUp") {}
        virtual ~MouseButtonUpEvent() {}
        int button = -1; // Mouse Button that was Up, 1 - LMB, 2 - MMB, 3 - RMB
    };
}

#endif // !MOUSE_EVENTS_H