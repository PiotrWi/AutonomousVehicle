#pragma once

#include "CommunicationProtocol/networking/AccessPoint.hpp"
#include <CommunicationProtocol/networking/MessageSender.hpp>
#include <CommunicationProtocol/networking/MessageDispatcher.hpp>
#include <EventLoop/EventLoop.hpp>

struct ApplicationContext
{
    ApplicationContext();
    networking::AccessPoint accessPoint_;
    networking::MessageDispatcher messageDispatcher_;
    networking::MessageSender<networking::AccessPoint> messageSender_;
    EventLoop eventLoop_;
};

