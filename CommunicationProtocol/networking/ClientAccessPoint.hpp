#pragma once

#include <functional>
#include <memory>
#include <optional>

#include <boost/asio.hpp>

#include "Tools/SingletonAddOn.hpp"
#include "Connection.hpp"

namespace networking
{

class ClientAccessPoint : public SingletonAddOn<ClientAccessPoint>
{
public:
    explicit ClientAccessPoint();
    bool connect();
    bool disconnect();
    bool isConnected();

    void send(std::string&& s);
    void send(std::vector<std::string>&& messages);

    void registerMessageCallback(std::function<void(std::string&)> callback);
    void registerConnectionStatusCallback(std::function<void(bool)> callback);
private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::socket sock_;

    std::unique_ptr<Connection> connection_;

    std::function<void(bool)> notifyAboutConnectionStateChange_;
    std::function<void(std::string&)> notifyMessage_;
};

} // networking
