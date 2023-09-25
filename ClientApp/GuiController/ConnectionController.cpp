#include "ConnectionController.hpp"

#include <Backend/RobotAccessPoint.hpp>

namespace gui_controller
{

bool ConnectionController::connect()
{
    return backend::RobotAccessPoint::getInstance().connect();
}

bool ConnectionController::disconnect()
{
    return backend::RobotAccessPoint::getInstance().disconnect();
}

void ConnectionController::registerConnectionChanged(std::function<void(bool)> callback_)
{
    notifyConnectionStatusChange_ = callback_;
    backend::RobotAccessPoint::getInstance().registerConnectionStatusCallback([&](auto status) {
        if (notifyConnectionStatusChange_) notifyConnectionStatusChange_(status);
    } );
}

}  // namespace gui_controller