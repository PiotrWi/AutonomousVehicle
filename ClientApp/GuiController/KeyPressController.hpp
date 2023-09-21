#pragma once

#include <QTimer>

namespace gui_controller
{

enum class Key
{
    Up,
    Down,
    Right,
    Left,
};

struct Speeds
{
    int leftMotorSpeed_;
    int rightMotorSpeed_;
};

std::optional<std::string> keyArrowToName(int keyNr);
std::optional<Key> keyArrowToEnumKey(int keyNr);

class KeyPressController
{
public:
    void start();
    void setKeyClicked();
    void setKeyReleased();

    Speeds getCurrentSetSpeeds();
private:
    QTimer timer_;
    Speeds currentSpeeds_;
    Speeds desiredSpeeds_;
};

}  // namespace gui_controller