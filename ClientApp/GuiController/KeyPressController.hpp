#pragma once

#include <QTimer>

#include <Tools/SingletonAddOn.hpp>

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

std::optional<std::string> keyArrowToName(int keyNr);
std::optional<Key> keyArrowToEnumKey(int keyNr);

class KeyPressController : public SingletonAddOn<KeyPressController>
{
public:
    void start();
    void setKeyClicked(Key);
    void setKeyReleased(Key);

    Speeds getCurrentSetSpeeds();
private:
    QTimer timer_;
    Speeds currentSpeeds_;
    Speeds desiredSpeeds_;

    bool keyPressed_[4];
};

}  // namespace gui_controller