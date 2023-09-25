#include "RobotComponent.hpp"

#include <EventLoop/MessageDecoder.hpp>

namespace components
{

RobotComponent::RobotComponent()
        : access_point_([this](const std::string& message){ eventLoop_.pushEvent(decode(message)); })
{
}

void RobotComponent::start()
{
    access_point_.start();

    while (true)
    {
        eventLoop_.dispatchEvent();
    }
}

std::unique_ptr<Component> createRobotComponent()
{
    return std::make_unique<RobotComponent>();
}

}