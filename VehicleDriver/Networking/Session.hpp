#pragma once

#include <functional>
#include <boost/asio.hpp>

namespace networking
{

class Session
{
public:
    explicit Session(boost::asio::ip::tcp::socket&& socket,
                     std::function<void()> notifyConnectionDroped,
                     std::function<void(const std::string&)> messageHandler);
    void start();
    void send(std::string message);
private:
    void receive_single();

    boost::asio::ip::tcp::socket socket_;
    std::mutex socketMutex_;
    std::function<void()> notifyConnectionDroped_;
    std::function<void(const std::string&)> messageHandler_;
};

}  // namespace networking
