#include "ApplicationContext.hpp"
#include <EventLoop/MessageDecoder.hpp>

// tmp: to be considered how to dispatch messages.
#include <SetSpeed.pb.h>

ApplicationContext::ApplicationContext()
    : accessPoint_()
    , messageSender_(accessPoint_)
{
    messageDispatcher_.subscribeFor(std::function<void(const SetSpeed&)>([&](auto&& msg){ eventLoop_.pushEvent(decode(msg)); }));

    accessPoint_.registerMessageCallback(
            [this](const std::string& message){ messageDispatcher_.dispatchMessage(message); }
    );

}
