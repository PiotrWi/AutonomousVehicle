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
private:
    void receive_single();

    boost::asio::ip::tcp::socket socket_;
    char data_[1024];
    boost::asio::mutable_buffer buffer_;
    std::function<void()> notifyConnectionDroped_;
};

}