#include "RobotAccessPoint.hpp"

#include <thread>

namespace backend
{

void RobotAccessPoint::start()
{
    auto asioReceiverThread = std::thread([&]()
    {
        io_service_.run();
    });
    asioReceiverThread.detach();
}

bool RobotAccessPoint::connect()
{
    return true;
}

} // backend