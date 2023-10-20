#include "MessageDecoder.hpp"

#include <sstream>

#include "GuiSpeedRequest.hpp"
#include <Tools/StringAlgorithms.hpp>

#include <SetSpeed.pb.h>

using namespace std;

NotHandledMessage::NotHandledMessage(const std::string& message)
    : std::logic_error("Not handled message"s + message )
{
}

/* Syntax: Set speed: LeftWheelSpeed<-100:100> RigthWheelSpeed <-100:100>
 */
Event decodeGuiSpeedRequest(const SetSpeed& message)
{
    auto* req = new GuiSpeedRequest();
    req->leftWheel_ = message.leftwheel();
    req->rightWheel_ = message.rightwheel();

    return {getId<GuiSpeedRequest>(), req};
}

Event decode(const google::protobuf::Message& message)
{
    if (message.GetTypeName() == "SetSpeed")
    {
        return decodeGuiSpeedRequest(static_cast<const SetSpeed&>(message));
    }
    throw NotHandledMessage(message.GetTypeName());
}
