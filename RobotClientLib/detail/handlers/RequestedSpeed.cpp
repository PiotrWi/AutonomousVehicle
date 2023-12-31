#include "RequestedSpeed.hpp"

#include <sstream>

#include <SetSpeed.pb.h>

#include "CommunicationProtocol/networking/ClientAccessPoint.hpp"
#include "CommunicationProtocol/networking/MessageSender.hpp"

void RequestedSpeed::handle(const CurrentRequestedSpeed& message)
{
    robot_interface::Speed speed;
    speed.leftWheel = message.leftwheel();
    speed.rightWheel = message.rightwheel();
    reactOnChange(speed);
}

void RequestedSpeed::setRequestedSpeed(robot_interface::Speed speed)
{
    SetSpeed setSpeed;
    setSpeed.set_leftwheel(speed.leftWheel);
    setSpeed.set_rightwheel(speed.rightWheel);

    networking::MessageSender(networking::ClientAccessPoint::getInstance()).send(std::move(setSpeed));
}

robot_interface::Speed RequestedSpeed::getRequestedSpeed()
{
    std::lock_guard<std::mutex> m(currentRequestedSpeed_mutex);
    return currentRequestedSpeed;
}

unsigned int RequestedSpeed::subscribeForRequestedSpeedChange(std::function<void(robot_interface::Speed )> callback)
{
    std::lock_guard<std::mutex> m(notifyClient_mutex);
    notifyClient_ = std::move(callback);
    return 0;
}

unsigned int RequestedSpeed::subscribeForRequestedSpeedChange(std::function<void(robot_interface::Speed )> callback,
                                                              robot_interface::Speed& outCurrentValue)
{
    std::lock_guard<std::mutex> m1(currentRequestedSpeed_mutex);
    std::lock_guard<std::mutex> m2(notifyClient_mutex);
    outCurrentValue = currentRequestedSpeed;
    notifyClient_ = std::move(callback);
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
