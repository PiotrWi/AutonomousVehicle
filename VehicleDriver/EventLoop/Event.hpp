#pragma once

class Event
{
public:
    template<typename TConcreteEvent>
    Event(unsigned int eventId, TConcreteEvent* concreteEvent)
        : eventId_(eventId)
        , payload_((void*)(concreteEvent))
    {
        deleter_ = [](void* payload){ delete (TConcreteEvent*)(payload); };
    }
    ~Event();

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    Event(Event&&) noexcept ;

    template<typename TConcreteEvent>
    TConcreteEvent* get()
    {
        return static_cast<TConcreteEvent*>(payload_);
    }
    unsigned int getId();
private:
    unsigned int eventId_;
    void *payload_ = nullptr;
    void(*deleter_)(void* payload) = nullptr;
};

template<typename TConcreteEvent>
unsigned int getId();