#pragma once

#include <functional>
#include <boost/asio.hpp>

namespace networking
{

class Session
{
public:
    explicit Session(boost::asio::ip::tcp::socket&& socket, std::function<void()> notifyConnectionDroped);
    void start();
    void send(std::string message);
private:
    void receive_single();

    boost::asio::ip::tcp::socket socket_;
    std::function<void()> notifyConnectionDroped_;
};

}  // namespace networking
