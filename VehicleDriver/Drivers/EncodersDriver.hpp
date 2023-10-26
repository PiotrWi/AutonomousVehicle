#pragma once

#include <VehicleDriver/Drivers/EPoolReactor/IEpollHandler.hpp>
#include <VehicleDriver/Drivers/EPoolReactor/EpollReactor.hpp>
#include <VehicleDriver/Drivers/GpioDriver.hpp>

namespace drivers
{

class EncoderDriver
{
public:
    explicit EncoderDriver(unsigned int c1Pin, unsigned int c2Pin);
    void init(drivers::epoll_reactor::EpollReactor&, std::function<void(int)> onC1Change, std::function<void(int)> onC2Change);

private:
    GpioInputDriverEpollHandler c1PortGpio_;
    GpioInputDriverEpollHandler c2PortGpio_;
};

} // drivers
