#pragma once

#include <functional>
#include <mutex>
#include <string>
#include "Types.hpp"

#include "IMessageHandler.hpp"

class RequestedSpeed : public IMessageHandler
{
public:
    void handle(const std::string& message) override;
    std::string getPrefix() override;
    void setRequestedSpeed(robot_interface::Speed);
    robot_interface::Speed getRequestedSpeed();
    unsigned int subscribeForRequestedSpeedChange(std::function<void(robot_interface::Speed )> callback);
    unsigned int subscribeForRequestedSpeedChange(std::function<void(robot_interface::Speed )> callback, robot_interface::Speed& outCurrentValue);

    void clear() override;
private:
    void reactOnChange(robot_interface::Speed);
    std::mutex currentRequestedSpeed_mutex;
    robot_interface::Speed currentRequestedSpeed = {0, 0};

    std::mutex notifyClient_mutex;
    std::function<void(robot_interface::Speed Speed)> notifyClient_;

};
