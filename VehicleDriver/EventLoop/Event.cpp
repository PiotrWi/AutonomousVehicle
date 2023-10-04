#include "Event.hpp"
#include <utility>

Event::~Event()
{
    if (payload_)
    {
        deleter_(payload_);
        payload_ = nullptr;
    }
}

unsigned int Event::getId()
{
    return eventId_;
}

Event::Event(Event &&other) noexcept
    : eventId_(other.eventId_)
{
    std::swap(other.deleter_, this->deleter_);
    std::swap(other.payload_, this->payload_);
}

