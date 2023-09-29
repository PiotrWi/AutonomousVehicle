
#include "KeyPressController.hpp"

#include "RobotClientLib/RobotInterface.hpp"

namespace gui_controller
{

std::optional<std::string> keyArrowToName(int keyNr)
{
    if (keyNr == Qt::Key::Key_Up) return "UP";
    if (keyNr == Qt::Key::Key_Down) return "DOWN";
    if (keyNr == Qt::Key::Key_Left) return "LEFT";
    if (keyNr == Qt::Key::Key_Right) return "RIGHT";
    return {};
}

std::optional<Key> keyArrowToEnumKey(int keyNr)
{
    if (keyNr == Qt::Key::Key_Up) return Key::Up;
    if (keyNr == Qt::Key::Key_Down) return Key::Down;
    if (keyNr == Qt::Key::Key_Left) return Key::Left;
    if (keyNr == Qt::Key::Key_Right) return Key::Right;
    return {};
}

Speeds &operator+=(Speeds &lhs, const Speeds &rhs)
{
    lhs.leftMotorSpeed_ += rhs.leftMotorSpeed_;
    lhs.rightMotorSpeed_ += rhs.rightMotorSpeed_;
    return lhs;
}

void KeyPressController::start()
{
    desiredSpeeds_ = {0, 0};
    sendRequestedSpeedToRobot();
}

void KeyPressController::sendRequestedSpeedToRobot()
{
    robot_interface::setRequestedSpeed(robot_interface::Speed{desiredSpeeds_.leftMotorSpeed_, desiredSpeeds_.rightMotorSpeed_});
}

void KeyPressController::stop()
{
    desiredSpeeds_ = {0, 0};
}

void KeyPressController::setKeyClicked(Key key)
{
    keyPressed_[static_cast<int>(key)] = true;
    if (key == Key::Up)
    {
        desiredSpeeds_ += Speeds{10, 10};
    }
    if (key == Key::Right)
    {
        desiredSpeeds_ += Speeds{-10, 10};
    }
    if (key == Key::Left)
    {
        desiredSpeeds_ += Speeds{10, -10};
    }
    if (key == Key::Down)
    {
        desiredSpeeds_ += Speeds{-10, -10};
    }

    sendRequestedSpeedToRobot();
}

void KeyPressController::setKeyReleased(Key key)
{
    keyPressed_[static_cast<int>(key)] = false;
}

void KeyPressController::subscribeToSpeeds(std::function<void(Speeds)> callback)
{
    robot_interface::subscribeForRequestedSpeedChange([callback](auto&& robotSpeeds) {
        callback({robotSpeeds.leftWheel, robotSpeeds.rightWheel});
    });
}

Speeds KeyPressController::getCurrentSetSpeeds()
{
    auto robotSpeeds = robot_interface::getRequestedSpeed();
    return {robotSpeeds.leftWheel, robotSpeeds.rightWheel};
}


}  // namespace gui_controller
