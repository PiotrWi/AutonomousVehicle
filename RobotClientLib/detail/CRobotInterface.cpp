#include "CRobotInterface.h"
#include "RobotInterface.hpp"

void c_init()
{
    robot_interface::init();
}

bool c_connect()
{
    return robot_interface::connect();
}

void c_disconnect()
{
    robot_interface::disconnect();
}

bool c_isConnected()
{
    return robot_interface::isConnected();
}

void c_subscribeForConnectionStatus(void (*callback)(bool))
{
    robot_interface::subscribeForConnectionStatus(callback);
}

void c_setRequestedSpeed(Speed speed)
{
    robot_interface::Speed ifSpeed {speed.leftWheel, speed.rightWheel};
    robot_interface::setRequestedSpeed(ifSpeed);
}

Speed c_getRequestedSpeed()
{
    auto ifSpeed = robot_interface::getRequestedSpeed();
    return Speed{ifSpeed.leftWheel, ifSpeed.rightWheel};
}

void c_subscribeForRequestedSpeedChange(void (*callback)(Speed))
{
    robot_interface::subscribeForRequestedSpeedChange([callback](auto&& ifSpeed){
        callback({ifSpeed.leftWheel, ifSpeed.rightWheel});
    });
}

