#include "Connection.hpp"

#include <iostream>
#include "CommunicationProtocol/Message.hpp"

#include "Tools/Checksum.hpp"

Connection::Connection(boost::asio::io_service& ioService,
                       boost::asio::ip::tcp::socket *socket,
                       std::function<void()> notifyConnectionDroped,
                       std::function<void(std::string&)> notifyMessageReceived)
        : ioService_(ioService)
        , socket_(socket)
        , notifyConnectionDroped_(std::move(notifyConnectionDroped))
        , notifyMessageReceived_(std::move(notifyMessageReceived))
{
}

void Connection::startReceiving()
{
    receive_single();
}

void Connection::startIoServiceAndReceiving()
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
    std::shared_ptr<std::array<char, SingleMessageMaxLen>> buff(new std::array<char, SingleMessageMaxLen>);
    auto buffer = boost::asio::buffer(*buff);
    std::lock_guard<std::mutex> lg(socketMutex_);
    socket_->async_receive(buffer, [&, keepAlive = buff, buffer](auto&& ec, auto&& bytes_transferred)
    {
        if (ec)
        {
            std::cerr << "Read failed" << std::endl;
            std::cerr << "EC: " << ec.what();
            notifyConnectionDroped_();
            return ;
        }
        std::string message(keepAlive->begin(), bytes_transferred);
        notifyMessageReceived_(message);
        receive_single();
    });
}

void Connection::send(std::string&& message)
{
    std::lock_guard<std::mutex> lk(socketMutex_);
    boost::asio::write(*socket_, boost::asio::buffer(message));
}

void Connection::send(std::vector<std::string>&& messages)
{
    std::lock_guard<std::mutex> lk(socketMutex_);
    for (auto msg : messages)
    {
        boost::asio::write(*socket_, boost::asio::buffer(msg));
    }

}
