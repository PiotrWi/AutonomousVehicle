#include "RobotAccessPoint.hpp"

#include <iostream>
#include <thread>

#include <boost/asio/ip/tcp.hpp>

namespace backend
{

RobotAccessPoint::RobotAccessPoint()
    : sock_(io_service_)
{
}

void RobotAccessPoint::start()
{
    auto asioReceiverThread = std::thread([&]()
    {
        io_service_.run();
    });
    asioReceiverThread.detach();
}

bool RobotAccessPoint::connect()
{
    boost::system::error_code ec;

    boost::asio::ip::tcp::endpoint endpoint{
        /*boost::asio::ip::address::from_string("172.16.1.64"),*/ boost::asio::ip::address::from_string("127.0.0.1"),
        17831
    };
    sock_.connect({endpoint}, ec);
    if (ec.value() != 0)
    {
        std::cerr << "connection failed" << std::endl;
        std::cerr << "ec: " << ec.what() << std::endl;
        if (notifyAboutConnectionStateChange_) notifyAboutConnectionStateChange_(false);
        return false;
    }
    if (notifyAboutConnectionStateChange_) notifyAboutConnectionStateChange_(true);
    return true;
}

bool RobotAccessPoint::disconnect()
{
    sock_.close();
    if (notifyAboutConnectionStateChange_) notifyAboutConnectionStateChange_(false);
    return true;
}

void RobotAccessPoint::registerConnectionStatusCallback(std::function<void(bool)> callback)
{
    notifyAboutConnectionStateChange_ = callback;
}

void RobotAccessPoint::send(std::string s)
{
    char data_[1024];
    strcpy(data_, s.c_str());
    boost::asio::mutable_buffer buffer_(data_, 1024);

    sock_.send(buffer_);
}

} // backend