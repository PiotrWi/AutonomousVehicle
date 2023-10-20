#pragma once

#include <mutex>
#include <optional>

#include <boost/asio.hpp>

#include "Tools/SingletonAddOn.hpp"
#include "Connection.hpp"

namespace networking
{

class AccessPoint
{
public:
    explicit AccessPoint();
    void send(std::string&& message);
    void send(std::vector<std::string>&& message);
    void registerMessageCallback(std::function<void(const std::string&)> callback);
    void start();
private:
    void accept_one();
private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket sock_;
    std::unique_ptr<Connection> connection_;
    std::mutex sessionMutex_;
    std::function<void(const std::string&)> messageHandler_;
};

}  // namespace networking
