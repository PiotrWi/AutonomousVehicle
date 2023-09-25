
#include "KeyPressController.hpp"

#include <Backend/RobotAccessPoint.hpp>

namespace
{

std::string createMessage(int leftWheel, int rightWheel)
{
    using namespace std;
    return "Set speed: "s + to_string(leftWheel) + " "s + to_string(rightWheel);
}

}  // namespace

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

void KeyPressController::start()
{
    desiredSpeeds_ = {0, 0};

}

void KeyPressController::setKeyClicked(Key key)
{
    keyPressed_[static_cast<int>(key)] = true;
    if (key == Key::Up)
    {
        desiredSpeeds_.leftMotorSpeed_ += 10;
        desiredSpeeds_.rightMotorSpeed_ += 10;
    }
    if (key == Key::Right)
    {
        desiredSpeeds_.leftMotorSpeed_ -= 10;
        desiredSpeeds_.rightMotorSpeed_ += 10;
    }
    if (key == Key::Left)
    {
        desiredSpeeds_.leftMotorSpeed_ += 10;
        desiredSpeeds_.rightMotorSpeed_ -= 10;
    }
    if (key == Key::Down)
    {
        desiredSpeeds_.leftMotorSpeed_ -= 10;
        desiredSpeeds_.rightMotorSpeed_ += 10;
    }

    backend::RobotAccessPoint::getInstance().send(
            createMessage(desiredSpeeds_.leftMotorSpeed_, desiredSpeeds_.rightMotorSpeed_));
}

void KeyPressController::setKeyReleased(Key key)
{
    keyPressed_[static_cast<int>(key)] = false;
}

}  // namespace gui_controller