#pragma once

#include <boost/asio.hpp>
#include <string>
#include <functional>

class Connection
{
public:
    explicit Connection(boost::asio::io_service&,
                        boost::asio::ip::tcp::socket* socket,
                        std::function<void()> notifyConnectionDroped,
                        std::function<void(std::string)>);

    void start();
    void send(std::string&& message);
private:
    void receive_single();

    boost::asio::io_service& ioService_;
    std::mutex socketMutex_;
    boost::asio::ip::tcp::socket* socket_;
    boost::asio::streambuf buffer_;
    std::function<void()> notifyConnectionDroped_;
    std::function<void(std::string)> notifyMessageReceived_;
};