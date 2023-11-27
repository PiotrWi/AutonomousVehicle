#include "EpollReactor.hpp"

#include <iostream>
#include <thread>

#include <unistd.h>

#include <sys/epoll.h>

namespace { const int MAX_EVENTS = 64;}

namespace drivers::epoll_reactor
{

void EpollReactor::run()
{
    epollDescriptor_ = FDRaiiWrapper(epoll_create1(0), [](auto fd){ close(fd); });
    if (epollDescriptor_.get() < 0)
    {
        perror("Failed to create epoll ");
    }

    epoll_event events[MAX_EVENTS];
    int i = 0;
    for (auto && [descriptor, handler] : handlerToDescriptors_)
    {
        events[i].data.fd = descriptor;
        events[i].events = EPOLLPRI | EPOLLET;
        auto ret = epoll_ctl(epollDescriptor_.get(), EPOLL_CTL_ADD, descriptor, &events[i]);
        if (ret < 0)
        {
            perror("failed to add epoll add");
        }
        i++
    }

    std::thread t([&](){
        while (true)
        {
            auto eventsCount = epoll_wait(epollDescriptor_.get(), events, MAX_EVENTS, -1);
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
