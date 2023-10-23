#pragma once

#include <functional>
#include <string>
#include "../../Tools/SingletonAddOn.hpp"

namespace gui_controller
{

class ConnectionController : public SingletonAddOn<ConnectionController>
{
public:
    static bool connect(const std::string& ip, unsigned int port);
    static void disconnect();
    void registerConnectionChanged(std::function<void(bool)> callback_);
private:
    std::function<void(bool)> notifyConnectionStatusChange_;
};

}  // namespace gui_controller
