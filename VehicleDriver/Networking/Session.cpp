#include "Session.hpp"

#include <iostream>
#include <string>

namespace networking
{

Session::Session(boost::asio::ip::tcp::socket&& socket,
                 std::function<void()> notifyConnectionDroped,
                 std::function<void(const std::string&)> messageHandler)
    : socket_(std::move(socket))
    , notifyConnectionDroped_(std::move(notifyConnectionDroped))
    , messageHandler_(std::move(messageHandler))
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
    std::lock_guard<std::mutex> lg(socketMutex_);
    socket_.async_receive(buffer, [&, keepAlive = buff, buffer](auto&& ec, auto&& bytes_transferred)
    {
        if (ec)
        {
            std::cerr << "Read failed" << std::endl;
            std::cerr << "EC: " << ec.what();
            notifyConnectionDroped_();
            return ;
        }
        std::string line(keepAlive->begin(), bytes_transferred);
        std::cout << line << std::endl;
        messageHandler_(line);
        receive_single();
    });
}

void Session::send(std::string&& message)
{
    std::lock_guard<std::mutex> lg(socketMutex_);
    socket_.send(boost::asio::buffer(message));
}

}  // namespace networking
