#include "EpollReactor.hpp"

#include <iostream>
#include <thread>

#include <unistd.h>

#include <sys/epoll.h>

namespace drivers::epoll_reactor
{

void EpollReactor::run()
{
    epollDescriptor_ = FDRaiiWrapper(epoll_create1(0), [](auto fd){ close(fd); });
    if (epollDescriptor_.get() < 0)
    {
        perror("Failed to create epoll ");
    }

    for (auto && [descriptor, handler] : handlerToDescriptors_)
    {
        epoll_event ee;
        ee.data.fd = descriptor;
        ee.events = EPOLLPRI | EPOLLET;
        auto ret = epoll_ctl(epollDescriptor_.get(), EPOLL_CTL_ADD, descriptor, &ee);
        if (ret < 0)
        {
            perror("failed to add epoll add");
        }
    }

    std::thread t([&](){
        epoll_event events[64];

        while (true)
        {
            auto eventsCount = epoll_wait(epollDescriptor_.get(), events, 64, -1);
            if (eventsCount < 0)
            {
                perror("epoll_wait failed");
            }
            for (auto i = 0; i < eventsCount; ++i)
            {
                auto readyFd = events[i].data.fd;
                handlerToDescriptors_[readyFd]->onAvailable(readyFd);
            }
        }
    });
    t.detach();
}

void EpollReactor::registerEpollHandler(IEpollHandler* handler)
{
    auto descriptors = handler->getDescriptorsToObserve();
    for (auto descriptor : descriptors)
    {
        handlerToDescriptors_.insert({descriptor, handler});
    }
}

}  // namespace drivers::epoll_reactor
