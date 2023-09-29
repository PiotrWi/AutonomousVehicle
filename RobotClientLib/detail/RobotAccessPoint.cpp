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
    std::cout << " RobotAccessPoint::start" << std::endl;
    auto asioReceiverThread = std::thread([&]()
    {
        std::cout << "RobotAccessPoint thread start" << std::endl;
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
        std::cout << "connection failed" << std::endl;
        std::cout << "ec: " << ec.what() << std::endl;

        messageReceiver_.reset();
        if (notifyAboutConnectionStateChange_) notifyAboutConnectionStateChange_(false);
        return false;
    }

    messageReceiver_ = MessageReceiver{&sock_, [this](){disconnect();}, notifyMessage_};
    if (notifyAboutConnectionStateChange_)
    {
        std::cout << "goint to call calback" << std::endl;
        notifyAboutConnectionStateChange_(true);
    }
    return true;
}

bool RobotAccessPoint::disconnect()
{
    sock_.close();
    messageReceiver_.reset();
    if (notifyAboutConnectionStateChange_) notifyAboutConnectionStateChange_(false);
    return true;
}

void RobotAccessPoint::registerConnectionStatusCallback(std::function<void(bool)> callback)
{
    notifyAboutConnectionStateChange_ = callback;
}

void RobotAccessPoint::registerMessageCallback(std::function<void(std::string)> callback)
{
    notifyMessage_ = callback;
}

void RobotAccessPoint::send(std::string s)
{
    if (not sock_.is_open())
        return;
    sock_.send(boost::asio::buffer(s));
}

bool RobotAccessPoint::isConnected()
{
    return sock_.is_open();
}

} // backend
