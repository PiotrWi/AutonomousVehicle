#pragma once

#include "SysHelper.hpp"

namespace drivers
{

class PwmDriver
{
public:
    explicit PwmDriver(int channel);
    ~PwmDriver();
    void init();
    void deinitialize();
    void set(unsigned int fill);
private:
    int channel_;
    bool isInitialized_;
    FDRaiiWrapper fd_;
};

}  // drivers
