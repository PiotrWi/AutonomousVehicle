#pragma once

#include <mutex>
#include <optional>

#include <boost/asio.hpp>

#include "Session.hpp"
#include <Tools/SingletonAddOn.hpp>

namespace networking
{

class AccessPoint
{
public:
    explicit AccessPoint(std::function<void(const std::string&)> messageHandler);
    void send(std::string&& message);
    void start();
private:
    void accept_one();
private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::unique_ptr<Session> session_;
    std::mutex sessionMutex_;
    std::function<void(const std::string&)> messageHandler_;
};

}  // namespace networking
