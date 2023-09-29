#include "AccessPoint.hpp"

#include <iostream>
#include <thread>

namespace networking
{

AccessPoint::AccessPoint(std::function<void(const std::string&)> messageHandler)
    : acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 17831))
    , messageHandler_(messageHandler)
{
}

void AccessPoint::start()
{
    std::thread t([&](){
        io_service_.run();
    });

    accept_one();

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
            std::cout << "Incomming connection" << std::endl;
            std::lock_guard<std::mutex> lg(sessionMutex_);
            session_ = Session(std::move(socket), [this]() {
                std::cout << "Connection dropped" << std::endl;
                session_ = {};
                accept_one();
            });
            session_->start();
        }
    });
}

void AccessPoint::send(std::string message)
{
    session_->send(message);

}

}  // namespace networking
