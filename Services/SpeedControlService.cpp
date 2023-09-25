//
// Created by pioter on 25.09.23.
//

#include "SpeedControlService.hpp"
#include <EventLoop/GuiSpeedRequest.hpp>

namespace services
{

SpeedControlService::SpeedControlService(EventLoop &el)
    : el_(el)
{
}

void SpeedControlService::start()
{
    motorsDrivers_.init();
    el_.subscribeForEvent<GuiSpeedRequest>([this](Event* ev){ this->reactOnGuiSpeedRequest(ev); });
}

void SpeedControlService::reactOnGuiSpeedRequest(Event *ev)
{
    auto speedRequest = ev->get<GuiSpeedRequest>();
    motorsDrivers_.setSpeed(speedRequest->leftWheel_, speedRequest->rightWheel_);
}

} // services