#pragma once

#include <Networking/AccessPoint.hpp>
#include <Networking/MessageSender.hpp>
#include <EventLoop/EventLoop.hpp>

struct ApplicationContext
{
    ApplicationContext();
    networking::AccessPoint accessPoint_;
    networking::MessageSender messageSender_;
    EventLoop eventLoop_;

};

