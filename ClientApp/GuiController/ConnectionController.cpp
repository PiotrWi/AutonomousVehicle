#include "ConnectionController.hpp"

#include <RobotClientLib/RobotInterface.hpp>

namespace gui_controller
{

bool ConnectionController::connect(const std::string& ip, unsigned int port)
{
    return robot_interface::connect(ip, port);
}

void ConnectionController::disconnect()
{
    return robot_interface::disconnect();
}

void ConnectionController::registerConnectionChanged(std::function<void(bool)> callback_)
{
    notifyConnectionStatusChange_ = std::move(callback_);
    robot_interface::subscribeForConnectionStatus([&](auto status) {
        if (notifyConnectionStatusChange_) notifyConnectionStatusChange_(status);
    } );
}

}  // namespace gui_controller
