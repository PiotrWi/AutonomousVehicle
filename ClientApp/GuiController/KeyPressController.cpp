
#include "KeyPressController.hpp"

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

}

void KeyPressController::setKeyClicked()
{

}

void KeyPressController::setKeyReleased()
{

}

}  // namespace gui_controller