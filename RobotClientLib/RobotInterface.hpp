#pragma once

#include <functional>
#include "Types.hpp"

namespace robot_interface
{

void init();

bool connect();
void disconnect();
bool isConnected();
void subscribeForConnectionStatus(std::function<void(bool )> callback);

void setRequestedSpeed(Speed);
Speed getRequestedSpeed();
void subscribeForRequestedSpeedChange(std::function<void(Speed )> callback);
void subscribeForRequestedSpeedChange(std::function<void(Speed )> callback, Speed& outCurrentValue);

}  // namespace robot_interface
