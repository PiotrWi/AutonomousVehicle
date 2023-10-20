#include "SpeedControlService.hpp"
#include "EventLoop/GuiSpeedRequest.hpp"
#include "EventLoop/MessageEncoder.hpp"

namespace services
{

SpeedControlService::SpeedControlService(EventLoop &el,
                                         networking::MessageSender<networking::AccessPoint>& messageSender)
    : el_(el)
    , messageSender_(messageSender)
{
}

void SpeedControlService::start()
{
    motorsDrivers_.init();
    requestedSpeedSubscription_ = el_.subscribeForEvent<GuiSpeedRequest>([this](Event* ev){ this->reactOnGuiSpeedRequest(ev); });
}

void SpeedControlService::reactOnGuiSpeedRequest(Event *ev)
{
    auto speedRequest = ev->get<GuiSpeedRequest>();
    std::cout << "reactOnGuiSpeedRequest: " << speedRequest->leftWheel_ << " " << speedRequest->rightWheel_ << std::endl;
    motorsDrivers_.setSpeed(speedRequest->leftWheel_, speedRequest->rightWheel_);
    messageSender_.send(createCurrentRequestedSpeed(speedRequest->leftWheel_, speedRequest->rightWheel_));
}

} // namespace services
