#pragma once

#include <EventLoop/EventLoop.hpp>
#include <Drivers/MotorsDriver.hpp>

namespace services
{

class SpeedControlService
{
public:
    explicit SpeedControlService(EventLoop& el);
    void start();
private:
    void reactOnGuiSpeedRequest(Event*);

    EventLoop& el_;
    drivers::MotorsDrivers motorsDrivers_;
};

} // services
