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

bool RobotAccessPoint::connect()
{
    boost::system::error_code ec;

    boost::asio::ip::tcp::endpoint endpoint{
        // boost::asio::ip::address::from_string("172.16.1.64"),
        boost::asio::ip::address::from_string("127.0.0.1"),
        17831
    };
    sock_.connect({endpoint}, ec);
    if (ec.value() != 0)
    {
        std::cout << "connection failed" << std::endl;
        std::cout << "ec: " << ec.what() << std::endl;

        connection_.reset();
        if (notifyAboutConnectionStateChange_) notifyAboutConnectionStateChange_(false);
        return false;
    }

    connection_ = std::make_unique<Connection>(io_service_, &sock_, [this](){disconnect();}, notifyMessage_);
    connection_->start();
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
    connection_.reset();
    if (notifyAboutConnectionStateChange_) notifyAboutConnectionStateChange_(false);
    return true;
}

void RobotAccessPoint::registerConnectionStatusCallback(std::function<void(bool)> callback)
{
    notifyAboutConnectionStateChange_ = std::move(callback);
}

void RobotAccessPoint::registerMessageCallback(std::function<void(std::string)> callback)
{
    notifyMessage_ = std::move(callback);
}

void RobotAccessPoint::send(std::string s)
{
    if (connection_)
    {
        connection_->send(std::move(s));
    }
}

bool RobotAccessPoint::isConnected()
{
    return sock_.is_open();
}

} // backend
