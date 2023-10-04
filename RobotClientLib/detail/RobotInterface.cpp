#include "../RobotInterface.hpp"

#include <iostream>
#include "RobotAccessPoint.hpp"
#include "RequestedSpeed.hpp"
#include "ImageHandler.hpp"
#include "MessageDispatcher.hpp"

namespace robot_interface
{

MessageDispatcher messageDispatcher_;
RequestedSpeed requestedSpeed_;
ImageHandler imageHandler_;

void clearModelOnConnectionChange(bool)
{

}

void init()
{
    std::cout << "[RobotInterface] c_init call" << std::endl;
    auto& robotAccessPoint = backend::RobotAccessPoint::getInstance();
    robotAccessPoint.start();
    robotAccessPoint.registerConnectionStatusCallback(clearModelOnConnectionChange);
    robotAccessPoint.registerMessageCallback([](auto&& message){
        messageDispatcher_.dispatchMessage(message);
    });

    messageDispatcher_.subscribeFor(requestedSpeed_.getPrefix(), [](auto&& message) {requestedSpeed_.handle(message); } );
    messageDispatcher_.subscribeFor(imageHandler_.getPrefix(), [](auto&& message) {imageHandler_.handle(message); } );
}

bool connect()
{
    std::cout << "[RobotInterface] c_connect call" << std::endl;
    auto isConnected = backend::RobotAccessPoint::getInstance().connect();
    std::cout << "[RobotInterface] c_connect return value: " << isConnected << std::endl;
    return isConnected;
}

void disconnect()
{
    std::cout << "[RobotInterface] c_disconnect call" << std::endl;
    backend::RobotAccessPoint::getInstance().disconnect();
}

bool isConnected()
{
    std::cout << "[RobotInterface] isConnected call" << std::endl;
    auto isConnected = backend::RobotAccessPoint::getInstance().isConnected();
    std::cout << "[RobotInterface] isConnected call return value: " << isConnected << std::endl;
    return isConnected;
}

void subscribeForConnectionStatus(std::function<void(bool)> callback)
{
    std::cout << "[RobotInterface] subscribeForConnectionStatus call" << std::endl;
    backend::RobotAccessPoint::getInstance().registerConnectionStatusCallback([callback](bool status){
        std::cout << "[RobotInterface] connection state change: " << status << std::endl;
        clearModelOnConnectionChange(status);
        callback(status);
    });
}

void setRequestedSpeed(Speed speed)
{
    std::cout << "[RobotInterface] setRequestedSpeed call with args: " << speed.leftWheel << " " << speed.rightWheel << std::endl;

    requestedSpeed_.setRequestedSpeed(speed);
}

Speed getRequestedSpeed()
{
    return requestedSpeed_.getRequestedSpeed();
}

void subscribeForRequestedSpeedChange(std::function<void(Speed )> callback)
{
    requestedSpeed_.subscribeForRequestedSpeedChange(callback);
}

void subscribeForRequestedSpeedChange(std::function<void(Speed )> callback, Speed& outCurrentValue)
{
    requestedSpeed_.subscribeForRequestedSpeedChange(callback, outCurrentValue);
}

void subscribeForPicture(CameraSide cameraSide, std::function<void(IntegerPicture)> callback)
{
    imageHandler_.subscribeForPicture(cameraSide, callback);
}

IntegerPicture getPicture(CameraSide cameraSide)
{
    return imageHandler_.getImage(cameraSide);
}

}  // namespace robot_interface
