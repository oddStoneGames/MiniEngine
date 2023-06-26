#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "KeyEvents.h"
#include "MouseEvents.h"
#include "WindowEvents.h"
#include <memory>

namespace MiniEngine
{
    class EventHandler
    {
    public:
        EventHandler() : WindowEventDispatcher(), MouseEventDispatcher(), KeyEventDispatcher() {}
        static EventHandler* GetInstance();

        // Window Events
        EventDispatcher<WindowEvents> WindowEventDispatcher;
        // Mouse Events
        EventDispatcher<MouseEvents> MouseEventDispatcher;
        // Keyboard Events
        EventDispatcher<KeyEvents> KeyEventDispatcher;
    private:
        static std::unique_ptr<EventHandler> s_Instance;
    };

#define ADD_WINDOW_EVENT_LISTENER(eventType, func, arg) EventHandler::GetInstance()->WindowEventDispatcher.AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));
#define ADD_MOUSE_EVENT_LISTENER(eventType, func, arg) EventHandler::GetInstance()->MouseEventDispatcher.AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));
#define ADD_KEY_EVENT_LISTENER(eventType, func, arg) EventHandler::GetInstance()->KeyEventDispatcher.AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));

#ifdef MINIENGINE_BUILD

#define SEND_WINDOW_EVENT(_event) EventHandler::GetInstance()->WindowEventDispatcher.SendEvent(_event)
#define SEND_MOUSE_EVENT(_event) EventHandler::GetInstance()->MouseEventDispatcher.SendEvent(_event)
#define SEND_KEY_EVENT(_event) EventHandler::GetInstance()->KeyEventDispatcher.SendEvent(_event)

#endif // MINIENGINE_BUILD
}

#endif // !EVENT_HANDLER_H
