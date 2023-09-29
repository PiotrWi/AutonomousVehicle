#include "Session.hpp"

#include <iostream>
#include <string>

namespace networking
{

Session::Session(boost::asio::ip::tcp::socket&& socket, std::function<void()> notifyConnectionDroped)
    : socket_(std::move(socket))
    , buffer_( boost::asio::buffer(data_, 1024))
    , notifyConnectionDroped_(notifyConnectionDroped)
{
}

void Session::start()
{
    receive_single();
}

void Session::receive_single()
{
    std::shared_ptr<std::array<char, 100>> buff(new std::array<char, 100>);
    auto buffer = boost::asio::buffer(*buff);
    socket_.async_receive(buffer, [&, keepAlive = buff, buffer](auto&& ec, auto&& bytes_transferred)
    {
        if (ec)
        {
            std::cerr << "Read failed" << std::endl;
            std::cerr << "EC: " << ec.what();
            notifyConnectionDroped_();
            return ;
        }
        std::string line(keepAlive.get()->begin(), bytes_transferred);
        std::cout << line << std::endl;

        receive_single();
    });
}

void Session::send(std::string message)
{
    socket_.send(boost::asio::buffer(message));
}

}  // namespace networking
