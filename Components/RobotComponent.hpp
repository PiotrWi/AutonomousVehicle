#pragma once

#include <memory>
#include "Component.hpp"

#include <EventLoop/EventLoop.hpp>
#include <Networking/AccessPoint.hpp>

namespace components
{

class RobotComponent : public Component
{
public:
    RobotComponent();
    void start() override;
private:
    EventLoop eventLoop_;
    networking::AccessPoint access_point_;
};

std::unique_ptr<Component> createRobotComponent();

}  // namespace components
