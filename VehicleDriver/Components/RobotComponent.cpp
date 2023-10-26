#include "RobotComponent.hpp"

namespace components
{

RobotComponent::RobotComponent(ApplicationContext& applicationContext)
        : eventLoop_(applicationContext.eventLoop_)
        , messageSender_(applicationContext.messageSender_)
        , speedControlService_(eventLoop_, messageSender_)
        , encoderService_(applicationContext.epollReactor_)
{
}

void RobotComponent::start()
{
    speedControlService_.start();
    encoderService_.start();
}

void RobotComponent::stop()
{

}

std::unique_ptr<Component> createRobotComponent(ApplicationContext& applicationContext)
{
    return std::make_unique<RobotComponent>(applicationContext);
}

}  // namespace components
