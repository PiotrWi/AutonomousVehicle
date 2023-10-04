#include "Connection.hpp"

#include <iostream>

Connection::Connection(boost::asio::io_service& ioService,
                       boost::asio::ip::tcp::socket *socket,
                       std::function<void()> notifyConnectionDroped,
                       std::function<void(std::string)> notifyMessageReceived)
        : ioService_(ioService)
        , socket_(socket)
        , notifyConnectionDroped_(notifyConnectionDroped)
        , notifyMessageReceived_(notifyMessageReceived)
{
}

void Connection::start()
{
    std::cout << " Connection::start" << std::endl;
    auto asioReceiverThread = std::thread([&]()
    {
        std::cout << "Connection thread start" << std::endl;
        ioService_.reset();
        receive_single();
        ioService_.run();
    });
    asioReceiverThread.detach();
}

void Connection::receive_single()
{
    boost::asio::async_read_until(*socket_, buffer_, '\n', [&](boost::system::error_code ec, std::size_t)
    {
        if (ec)
        {
            notifyConnectionDroped_();
            return ;
        }
        std::istream input_stream(&buffer_);
        std::string message;
        std::getline(input_stream, message);

        notifyMessageReceived_(message);

        receive_single();
    });
}

void Connection::send(std::string message)
{
    socket_->send(boost::asio::buffer(message));
}

