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

#define AddWindowEventListener(eventType, func, arg) EventHandler::GetInstance()->WindowEventDispatcher.AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));
#define AddMouseEventListener(eventType, func, arg) EventHandler::GetInstance()->MouseEventDispatcher.AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));
#define AddKeyEventListener(eventType, func, arg) EventHandler::GetInstance()->KeyEventDispatcher.AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));

#define RemoveWindowEventListener(handle) EventHandler::GetInstance()->WindowEventDispatcher.RemoveListener(handle);
#define RemoveMouseEventListener(handle) EventHandler::GetInstance()->MouseEventDispatcher.RemoveListener(handle);
#define RemoveKeyEventListener(handle) EventHandler::GetInstance()->KeyEventDispatcher.RemoveListener(handle);

#ifdef MINIENGINE_BUILD

#define SendWindowEvent(_event) EventHandler::GetInstance()->WindowEventDispatcher.SendEvent(_event)
#define SendMouseEvent(_event) EventHandler::GetInstance()->MouseEventDispatcher.SendEvent(_event)
#define SendKeyEvent(_event) EventHandler::GetInstance()->KeyEventDispatcher.SendEvent(_event)

#endif // MINIENGINE_BUILD
}

#endif // !EVENT_HANDLER_H
