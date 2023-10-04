#include "RobotComponent.hpp"

#include "EventLoop/MessageDecoder.hpp"

namespace components
{

RobotComponent::RobotComponent(ApplicationContext& applicationContext)
        : eventLoop_(applicationContext.eventLoop_)
        , access_point_(applicationContext.accessPoint_)
        , messageSender_(applicationContext.messageSender_)
        , speedControlService_(eventLoop_, messageSender_)
{
}

void RobotComponent::start()
{
    speedControlService_.start();
}

std::unique_ptr<Component> createRobotComponent(ApplicationContext& applicationContext)
{
    return std::make_unique<RobotComponent>(applicationContext);
}

}  // namespace components
