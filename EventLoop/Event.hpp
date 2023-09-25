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

    template<typename TConcreteEvent>
    TConcreteEvent* get()
    {
        return static_cast<TConcreteEvent*>(payload_);
    }
    unsigned int getId();
private:
    unsigned int eventId_;
    void *payload_;
    void(*deleter_)(void* payload);
};

template<typename TConcreteEvent>
unsigned int getId();
