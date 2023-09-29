#include "Event.hpp"

Event::~Event()
{
    deleter_(payload_);
}

unsigned int Event::getId()
{
    return eventId_;
}
