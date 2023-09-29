#pragma once

#include "SysHelper.hpp"

namespace drivers
{

class GpioOutputDriver
{
public:
    explicit GpioOutputDriver(int pinNr);
    ~GpioOutputDriver();
    void init();
    void deinitialize();
    void setHigh();
    void setLow();

private:
    const int pinNr_;
    bool isInitialized_;
    FDRaiiWrapper fd_;
};

}  // drivers
