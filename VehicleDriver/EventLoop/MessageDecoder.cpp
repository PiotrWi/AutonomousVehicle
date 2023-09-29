#include "MessageDecoder.hpp"

#include <sstream>

#include "GuiSpeedRequest.hpp"
#include "../../Tools/StringAlgorithms.hpp"

NotHandledMessage::NotHandledMessage()
    : std::logic_error("Not handled message")
{
}

/* Syntax: Set speed: LeftWheelSpeed<-100:100> RigthWheelSpeed <-100:100>
 */
Event decodeGuiSpeedRequest(const std::string message)
{
    auto* req = new GuiSpeedRequest();
    auto speeds = splitAndTrim(message, ':')[1];

    std::stringstream ss(speeds);
    ss >> req->leftWheel_ >> req->rightWheel_;

    return Event(getId<GuiSpeedRequest>(), req);
}

Event decode(std::string message)
{
    if (message.starts_with("Set speed: "))
    {
        return decodeGuiSpeedRequest(message);
    }
    throw NotHandledMessage();
}
