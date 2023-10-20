#include "../RobotInterface.hpp"

#include <iostream>
#include "RobotClientLib/detail/handlers/RequestedSpeed.hpp"
#include "RobotClientLib/detail/handlers/ImageHandler.hpp"
#include "CommunicationProtocol/networking/MessageDispatcher.hpp"
#include "CommunicationProtocol/networking/ClientAccessPoint.hpp"

namespace robot_interface
{

networking::MessageDispatcher messageDispatcher_;
RequestedSpeed requestedSpeed_;
ImageHandler imageHandler_;

void clearModelOnConnectionChange(bool)
{
    requestedSpeed_.clear();
    imageHandler_.clear();
}

// Connection interfaces
void init()
{
    std::cout << "[RobotInterface] init call" << std::endl;
    auto& robotAccessPoint = networking::ClientAccessPoint::getInstance();

    robotAccessPoint.registerConnectionStatusCallback(clearModelOnConnectionChange);
    robotAccessPoint.registerMessageCallback([](auto&& message){
        messageDispatcher_.dispatchMessage(message);
    });

    messageDispatcher_.subscribeFor(std::function<void(const CurrentRequestedSpeed&)>([](const CurrentRequestedSpeed& message) { requestedSpeed_.handle(message); }));
    messageDispatcher_.subscribeFor(std::function<void(const PublishImage&)>([](const PublishImage& message) { imageHandler_.handle(message); } ));
}

bool connect()
{
    std::cout << "[RobotInterface] connect call" << std::endl;
    auto isConnected = networking::ClientAccessPoint::getInstance().connect();
    std::cout << "[RobotInterface] connect return value: " << isConnected << std::endl;
    return isConnected;
}

void disconnect()
{
    std::cout << "[RobotInterface] disconnect call" << std::endl;
    networking::ClientAccessPoint::getInstance().disconnect();
}

bool isConnected()
{
    std::cout << "[RobotInterface] isConnected call" << std::endl;
    auto isConnected = networking::ClientAccessPoint::getInstance().isConnected();
    std::cout << "[RobotInterface] isConnected call return value: " << isConnected << std::endl;
    return isConnected;
}

void subscribeForConnectionStatus(std::function<void(bool)> callback)
{
    std::cout << "[RobotInterface] subscribeForConnectionStatus call" << std::endl;
    networking::ClientAccessPoint::getInstance().registerConnectionStatusCallback([callback](bool status){
        std::cout << "[RobotInterface] connection state change: " << status << std::endl;
        clearModelOnConnectionChange(status);
        callback(status);
    });
}

// Speed interfaces
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

// Picture interfaces
void subscribeForPicture(CameraSide cameraSide, std::function<void(IntegerPicture)> callback)
{
    imageHandler_.subscribeForPicture(cameraSide, callback);
}

IntegerPicture getPicture(CameraSide cameraSide)
{
    return imageHandler_.getImage(cameraSide);
}

}  // namespace robot_interface
