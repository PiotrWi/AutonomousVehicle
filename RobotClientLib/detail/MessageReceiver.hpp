#pragma once

#include <boost/asio.hpp>
#include <string>
#include <functional>

class MessageReceiver
{
public:
    explicit MessageReceiver(boost::asio::ip::tcp::socket* socket,
                             std::function<void()> notifyConnectionDroped,
                             std::function<void(std::string)>);
    void start();
private:
    void receive_single();

    // TODO: asio socket is not thread safety. As such, it has to be wrapped, or redesigned.
    boost::asio::ip::tcp::socket* socket_;
    char data_[1024];
    boost::asio::mutable_buffer buffer_;
    std::function<void()> notifyConnectionDroped_;
    std::function<void(std::string)> notifyMessageReceived_;
};
