#include "ApplicationContext.hpp"
#include <EventLoop/MessageDecoder.hpp>

ApplicationContext::ApplicationContext()
    : accessPoint_([this](const std::string& message){ eventLoop_.pushEvent(decode(message)); })
    , messageSender_(accessPoint_)
{

}
