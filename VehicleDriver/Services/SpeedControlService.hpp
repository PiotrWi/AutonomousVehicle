#pragma once

#include "EventLoop/EventLoop.hpp"
#include "Drivers/MotorsDriver.hpp"
#include "Networking/MessageSender.hpp"

namespace services
{

class SpeedControlService
{
public:
    explicit SpeedControlService(EventLoop& el, networking::MessageSender& messageSender);
    void start();
private:
    void reactOnGuiSpeedRequest(Event*);

    EventLoop& el_;
    drivers::MotorsDrivers motorsDrivers_;
    networking::MessageSender messageSender_;
};

} // services
