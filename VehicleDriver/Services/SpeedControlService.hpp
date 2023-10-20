#pragma once

#include "EventLoop/EventLoop.hpp"
#include "Drivers/MotorsDriver.hpp"
#include "CommunicationProtocol/networking/MessageSender.hpp"
#include "CommunicationProtocol/networking/AccessPoint.hpp"

namespace services
{

class SpeedControlService
{
public:
    explicit SpeedControlService(EventLoop& el, networking::MessageSender<networking::AccessPoint>& messageSender);
    void start();
private:
    void reactOnGuiSpeedRequest(Event*);

    EventLoop& el_;
    drivers::MotorsDrivers motorsDrivers_;
    networking::MessageSender<networking::AccessPoint> messageSender_;
    EventLoop::SubscriptionPtr requestedSpeedSubscription_;
};

} // services
