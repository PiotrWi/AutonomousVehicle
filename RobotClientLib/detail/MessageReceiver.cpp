#include "MessageReceiver.hpp"

#include <iostream>

MessageReceiver::MessageReceiver(boost::asio::ip::tcp::socket* socket,
                                 std::function<void()> notifyConnectionDroped,
                                 std::function<void(std::string)> notifyMessageReceived)
        : socket_(socket)
        , buffer_(data_, 1024)
        , notifyConnectionDroped_(notifyConnectionDroped)
        , notifyMessageReceived_(notifyMessageReceived)
{
}

void MessageReceiver::start()
{
    receive_single();
}

void MessageReceiver::receive_single()
{
    socket_->async_receive(buffer_, [&](auto&& ec, auto&& bytes_transferred)
    {
        if (ec)
        {
            notifyConnectionDroped_();
            return ;
        }
        std::string line(data_, bytes_transferred);
        notifyMessageReceived_(line);

        receive_single();
    });
}
