#include "ClientAccessPoint.hpp"

#include <iostream>
#include <thread>

#include <boost/asio/ip/tcp.hpp>

namespace networking
{

ClientAccessPoint::ClientAccessPoint()
    : sock_(io_service_)
{
}

bool ClientAccessPoint::connect(const std::string& ip, unsigned int port)
{
    boost::system::error_code ec;

    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address::from_string(ip),
        port);
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
    connection_->startIoServiceAndReceiving();
    if (notifyAboutConnectionStateChange_)
    {
        std::cout << "going to call calback" << std::endl;
        notifyAboutConnectionStateChange_(true);
    }
    return true;
}

bool ClientAccessPoint::disconnect()
{
    sock_.close();
    connection_.reset();
    if (notifyAboutConnectionStateChange_) notifyAboutConnectionStateChange_(false);
    return true;
}

void ClientAccessPoint::registerConnectionStatusCallback(std::function<void(bool)> callback)
{
    notifyAboutConnectionStateChange_ = std::move(callback);
}

void ClientAccessPoint::registerMessageCallback(std::function<void(std::string&)> callback)
{
    notifyMessage_ = std::move(callback);
}

void ClientAccessPoint::send(std::string&& s)
{
    if (connection_)
    {
        connection_->send(std::move(s));
    }
}

void ClientAccessPoint::send(std::vector<std::string>&& messages)
{
    if (connection_)
    {
        connection_->send(std::move(messages));
    }
}

bool ClientAccessPoint::isConnected()
{
    return sock_.is_open();
}

} // networking
