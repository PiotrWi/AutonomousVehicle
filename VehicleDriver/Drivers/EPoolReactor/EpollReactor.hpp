#pragma once

#include <map>
#include <vector>

#include "IEpollHandler.hpp"
#include "VehicleDriver/Drivers/Helpers/FDRaiiWrapper.hpp"

namespace drivers::epoll_reactor
{

class EpollReactor
{
public:
    void run();
    void registerEpollHandler(IEpollHandler*);
private:
    FDRaiiWrapper epollDescriptor_;
    std::map<int, IEpollHandler*> handlerToDescriptors_;
};

}  // namespace drivers::epoll_reactor