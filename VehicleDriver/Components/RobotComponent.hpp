#pragma once

#include <memory>
#include "Component.hpp"
#include "../ApplicationContext.hpp"

#include "EventLoop/EventLoop.hpp"
#include "Networking/AccessPoint.hpp"
#include "Networking/MessageSender.hpp"
#include "Services/SpeedControlService.hpp"

namespace components
{

class RobotComponent : public Component
{
public:
    explicit RobotComponent(ApplicationContext& applicationContext);
    void start() override;
private:
    EventLoop& eventLoop_;
    networking::AccessPoint& access_point_;
    networking::MessageSender& messageSender_;

    services::SpeedControlService speedControlService_;
};

std::unique_ptr<Component> createRobotComponent(ApplicationContext& applicationContext);

}  // namespace components
