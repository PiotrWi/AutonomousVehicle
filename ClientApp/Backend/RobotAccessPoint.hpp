#pragma once

#include <functional>

#include <boost/asio.hpp>  // to be hidden later on

#include <Tools/SingletonAddOn.hpp>

namespace backend
{

class RobotAccessPoint : public SingletonAddOn<RobotAccessPoint>
{
public:
    RobotAccessPoint();
    void start();
    bool connect();
    bool disconnect();

    void send(std::string s);

    void registerConnectionStatusCallback(std::function<void(bool)> callback);
private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::socket sock_;
    std::function<void(bool)> notifyAboutConnectionStateChange_;
};

} // backend
