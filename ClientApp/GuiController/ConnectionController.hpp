#pragma once

#include <functional>
#include "../../Tools/SingletonAddOn.hpp"

namespace gui_controller
{

class ConnectionController : public SingletonAddOn<ConnectionController>
{
public:
    bool connect();
    void disconnect();
    void registerConnectionChanged(std::function<void(bool)> callback_);
private:
    std::function<void(bool)> notifyConnectionStatusChange_;
};

}  // namespace gui_controller
