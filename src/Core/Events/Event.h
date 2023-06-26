#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <map>
#include <functional>
#include <vector>

namespace MiniEngine
{
    /**
    @brief Base class for all events.
    */
    template <typename T>
    class Event
    {
    protected:
        T m_Type;
        std::string m_Name;
        bool m_Handled = false;
    public:
        Event() = default;
        Event(T type, const std::string& name = "") : m_Type(type), m_Name(name) {}
        virtual ~Event() {}
        inline const T GetType() const { return m_Type; }

        template<typename EventType>
        inline EventType ToType() const
        {
            return static_cast<const EventType&>(*this);
        }

        inline const std::string& GetName() const { return m_Name; }
        virtual bool Handled() const { return m_Handled; }
    };

    /**
    @brief Dispatches events to listener.
    SendEvent(): Submit a given event to all the listeners.
    AddListener(): Become a listener of an Event.
    */
    template<typename T>
    class EventDispatcher
    {
    private:
        using Func = std::function<void(const Event<T>&)>;
        std::map<T, std::vector<Func>> m_Listeners;
    public:
        /// @brief Add an Listener to the type of event.
        /// @param type Event Type
        /// @param func Listener Function
        void AddListener(T type, const Func& func)
        {
            m_Listeners[type].push_back(func);
        }

#ifdef MINIENGINE_BUILD // To make sure Send Event is only accessible in the Mini Engine Project.

        /// @brief Sends the event to all its listeners.
        /// @param event Event To Send.
        void SendEvent(const Event<T>& event)
        {
            if (m_Listeners.find(event.GetType()) == m_Listeners.end())
                return; // Return if no Listner is there for this event.

            // Loop though all Listeners. If the event is not handled yet, we continue to process it.
            for (auto&& listener : m_Listeners.at(event.GetType())) {
                if (!event.Handled()) listener(event);
            }
        }

#endif // MINIENGINE_BUILD

    };
}

#endif // !EVENT_H