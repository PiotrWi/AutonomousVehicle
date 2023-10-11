#include "CRobotInterface.h"

#include <cstring>

#include "RobotInterface.hpp"

// Connection interfaces
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

// Speed interfaces
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

// Picture interfaces
namespace
{

robot_interface::CameraSide translateSide(Side s)
{
    if (s == Side::Left)
    {
        return robot_interface::CameraSide::Left;
    }
    return robot_interface::CameraSide::Right;
}

IntegerPicture translatePicture(robot_interface::IntegerPicture& robotIntegerPicture)
{
    IntegerPicture integerPicture;

    integerPicture.format = robotIntegerPicture.format;
    integerPicture.rows = robotIntegerPicture.rows;
    integerPicture.columns = robotIntegerPicture.columns;
    integerPicture.pixels = new unsigned char(robotIntegerPicture.pixels.size());

    memcpy(integerPicture.pixels, robotIntegerPicture.pixels.data(), robotIntegerPicture.pixels.size());

    return integerPicture;
}

}  // namespace

void c_free_IntegerPicture(IntegerPicture* ip)
{
    delete[] ip->pixels;
}

IntegerPicture c_getPicture(Side side)
{
    auto robotImagePicture = robot_interface::getPicture(translateSide(side));
    return translatePicture(robotImagePicture);
}

void c_subscribeForPicture(Side side, void (*callback)(IntegerPicture))
{
    robot_interface::subscribeForPicture(translateSide(side),
        [callback](auto&& robotIntegerPicture){
            callback(translatePicture(robotIntegerPicture));
    });
}
