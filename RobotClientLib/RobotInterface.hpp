#pragma once

#include <functional>
#include <string>
#include "Types.hpp"

namespace robot_interface
{

// Connection interfaces
void init();

bool connect(const std::string& ip, unsigned int port);
void disconnect();
bool isConnected();
void subscribeForConnectionStatus(std::function<void(bool )> callback);

// Speed interfaces
void setRequestedSpeed(Speed);
Speed getRequestedSpeed();
void subscribeForRequestedSpeedChange(std::function<void(Speed )> callback);
void subscribeForRequestedSpeedChange(std::function<void(Speed )> callback, Speed& outCurrentValue);

// Picture interfaces
IntegerPicture getPicture(CameraSide);
void subscribeForPicture(CameraSide, std::function<void(IntegerPicture)> callback);

}  // namespace robot_interface
