#include "RequestedSpeed.hpp"

#include <sstream>

#include "RobotAccessPoint.hpp"

void RequestedSpeed::handle(const std::string& message)
{
    std::stringstream ss(message.substr(getPrefix().size()));
    robot_interface::Speed speed;
    ss >> speed.leftWheel >> speed.rightWheel;
    reactOnChange(speed);
}

std::string RequestedSpeed::getPrefix()
{
    return std::string("CurrentRequestedSpeed:");
}

void RequestedSpeed::setRequestedSpeed(robot_interface::Speed speed)
{
    using namespace std;
    auto message = "Set speed: "s + to_string(speed.leftWheel) + " "s + to_string(speed.rightWheel) + "/n";
    backend::RobotAccessPoint::getInstance().send(message);
}

robot_interface::Speed RequestedSpeed::getRequestedSpeed()
{
    std::lock_guard<std::mutex> m(currentRequestedSpeed_mutex);
    return currentRequestedSpeed;
}

unsigned int RequestedSpeed::subscribeForRequestedSpeedChange(std::function<void(robot_interface::Speed )> callback)
{
    std::lock_guard<std::mutex> m(notifyClient_mutex);
    notifyClient_ = callback;
    return 0;
}

unsigned int RequestedSpeed::subscribeForRequestedSpeedChange(std::function<void(robot_interface::Speed )> callback,
                                                              robot_interface::Speed& outCurrentValue)
{
    std::lock_guard<std::mutex> m1(currentRequestedSpeed_mutex);
    std::lock_guard<std::mutex> m2(notifyClient_mutex);
    outCurrentValue = currentRequestedSpeed;
    notifyClient_ = callback;
    return 0;
}

void RequestedSpeed::reactOnChange(robot_interface::Speed speed)
{
    {
        std::lock_guard<std::mutex> m(currentRequestedSpeed_mutex);
        currentRequestedSpeed = speed;
    }
    {
        std::lock_guard<std::mutex> m(notifyClient_mutex);
        if (notifyClient_)
            notifyClient_(speed);
    }
}

void RequestedSpeed::clear()
{
    reactOnChange(robot_interface::Speed{0, 0});
}
