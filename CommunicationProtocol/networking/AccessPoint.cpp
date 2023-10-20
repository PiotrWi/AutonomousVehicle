#include "AccessPoint.hpp"

#include <iostream>
#include <thread>

namespace networking
{

AccessPoint::AccessPoint()
    : acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 17831))
    , sock_(io_service_)
{
}

void AccessPoint::start()
{
    std::thread t([&](){
        accept_one();
        io_service_.run();
        std::cout << "Why end??";
    });

    t.detach();
}

void AccessPoint::accept_one()
{
    acceptor_.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::tcp::socket socket) {
        if (ec)
        {
            std::cerr << "Accepting failed" << std::endl;
            std::cerr << "EC: " << ec.what();
            accept_one();
            return;
        }
        {
            sock_ = std::move(socket);
            std::cout << "Incomming connection" << std::endl;
            std::lock_guard<std::mutex> lg(sessionMutex_);
            connection_ = std::make_unique<Connection>(
                    io_service_,
                    &sock_,
                    [this]() {
                        std::cout << "Connection dropped" << std::endl;
                        connection_ = {};
                        accept_one();
                        },
                    messageHandler_);
            connection_->startReceiving();
        }
    });
}

void AccessPoint::send(std::string&& message)
{
    if (connection_)
    {
        connection_->send(std::move(message));
    }
}

void AccessPoint::send(std::vector<std::string>&& messages)
{
    if (messages.empty())
    {
        std::cerr << "AccessPoint::send called with empty messages." << std::endl;
    }
    if (connection_)
    {
        connection_->send(std::move(messages));
    }
}

void AccessPoint::registerMessageCallback(std::function<void(const std::string &)> callback)
{
    messageHandler_ = callback;
}

}  // namespace networking
