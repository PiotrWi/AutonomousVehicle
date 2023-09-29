#pragma once

#include <QTimer>

#include "../../Tools/SingletonAddOn.hpp"

namespace gui_controller
{

enum class Key
{
    Up = 0,
    Down = 1,
    Right = 2,
    Left = 3,
};

struct Speeds
{
    int leftMotorSpeed_;
    int rightMotorSpeed_;
};

Speeds& operator+=(Speeds&, const Speeds&);

std::optional<std::string> keyArrowToName(int keyNr);
std::optional<Key> keyArrowToEnumKey(int keyNr);

class KeyPressController : public SingletonAddOn<KeyPressController>
{
public:
    void start();
    void stop();

    void setKeyClicked(Key);
    void setKeyReleased(Key);

    void subscribeToSpeeds(std::function<void(Speeds)> callback);
    Speeds getCurrentSetSpeeds();
private:
    void sendRequestedSpeedToRobot();

    QTimer timer_;
    Speeds desiredSpeeds_;

    std::function<void(int, int)> onRequestedSpeedChanged_;

    bool keyPressed_[4];
};

}  // namespace gui_controller
