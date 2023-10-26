#pragma once

#include <vector>

namespace drivers::epoll_reactor
{

class IEpollHandler
{
public:
    virtual std::vector<int> getDescriptorsToObserve() const = 0;
    virtual void onAvailable(int descriptor) = 0;
};

}  // namespace drivers::epoll_reactor
