#pragma once

#include <memory>
#include "Component.hpp"
#include "../ApplicationContext.hpp"

#include "EventLoop/EventLoop.hpp"
#include "CommunicationProtocol/networking/AccessPoint.hpp"
#include <CommunicationProtocol/networking/MessageSender.hpp>
#include "Services/SpeedControlService.hpp"

namespace components
{

class RobotComponent : public Component
{
public:
    explicit RobotComponent(ApplicationContext& applicationContext);
    void start() override;
    void stop() override;
private:
    EventLoop& eventLoop_;
    networking::MessageSender<networking::AccessPoint>& messageSender_;

    services::SpeedControlService speedControlService_;
};

std::unique_ptr<Component> createRobotComponent(ApplicationContext& applicationContext);

}  // namespace components
