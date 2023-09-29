#include "ConnectionController.hpp"

#include <RobotClientLib/RobotInterface.hpp>

namespace gui_controller
{

bool ConnectionController::connect()
{
    return robot_interface::connect();
}

void ConnectionController::disconnect()
{
    return robot_interface::disconnect();
}

void ConnectionController::registerConnectionChanged(std::function<void(bool)> callback_)
{
    notifyConnectionStatusChange_ = callback_;
    robot_interface::subscribeForConnectionStatus([&](auto status) {
        if (notifyConnectionStatusChange_) notifyConnectionStatusChange_(status);
    } );
}

}  // namespace gui_controller
