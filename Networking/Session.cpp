#include "Session.hpp"

#include <iostream>
#include <string>

namespace networking
{

Session::Session(boost::asio::ip::tcp::socket&& socket, std::function<void()> notifyConnectionDroped)
    : socket_(std::move(socket))
    , buffer_(data_, 1024)
    , notifyConnectionDroped_(notifyConnectionDroped)
{
}

void Session::start()
{
    receive_single();
}

void Session::receive_single()
{
    socket_.async_receive(buffer_, [&](auto&& ec, auto&& bytes_transferred)
    {
        if (ec)
        {
            std::cerr << "Read failed" << std::endl;
            std::cerr << "EC: " << ec.what();
            notifyConnectionDroped_();
            return ;
        }
        std::string line(data_, bytes_transferred);
        std::cout << line << std::endl;

        receive_single();
    });
}

}  // namespace networking
