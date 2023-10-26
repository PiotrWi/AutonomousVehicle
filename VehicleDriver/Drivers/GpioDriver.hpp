#pragma once

#include <functional>

#include "VehicleDriver/Drivers/Helpers/SysHelper.hpp"
#include "VehicleDriver/Drivers/detail/GpioDriverBase.hpp"
#include <VehicleDriver/Drivers/EPoolReactor/IEpollHandler.hpp>

namespace drivers
{

extern const char in[];
extern const char out[];

class GpioInputDriver
    : public GpioDriverBase<in>

{
public:
    explicit GpioInputDriver(int pinNr);
    ~GpioInputDriver();
    void init();
    int read();
};

class GpioOutputDriver : public GpioDriverBase<out>
{
public:
    explicit GpioOutputDriver(int pinNr);
    ~GpioOutputDriver();
    void init();
    void setHigh();
    void setLow();
};

class GpioInputDriverEpollHandler
    : public GpioInputDriver
    , public epoll_reactor::IEpollHandler
{
public:
    explicit GpioInputDriverEpollHandler(int pinNr);
    void init(std::function<void(bool)> onChange);
    std::vector<int> getDescriptorsToObserve() const override;
    void onAvailable(int descriptors) override;
private:
    void initEdges();
    void readEdges();

    std::function<void(bool)> onChange_;
    std::string buffer_;
};

}  // drivers
