#pragma once

#include <functional>
#include <mutex>
#include <string>
#include "Types.hpp"

#include "IMessageHandler.hpp"
#include <CurrentRequestedSpeed.pb.h>

class RequestedSpeed : public IMessageHandler<CurrentRequestedSpeed>
{
public:
    void handle(const CurrentRequestedSpeed& message) override;
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
