#pragma once

#include <boost/asio.hpp>  // to be hidden later on

namespace backend
{

class RobotAccessPoint
{
public:
    void start();
    bool connect();
private:
    boost::asio::io_service io_service_;
};

} // backend
