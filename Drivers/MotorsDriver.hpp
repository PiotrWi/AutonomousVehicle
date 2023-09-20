#pragma once

#include "MotorsDriver.hpp"
#include "GpioDriver.hpp"
#include "PwmDriver.hpp"

namespace drivers
{

class MotorsDrivers
{
public:
    MotorsDrivers();
    ~MotorsDrivers();
    void init();
    void deinitialize();

    void stop();
    void setSpeed(int leftMotor, int rightMotor);
private:
    GpioOutputDriver phasePinLeftMotor_;
    GpioOutputDriver phasePinRightMotor_;

    PwmDriver leftMotorPwm_;
    PwmDriver rightMotorPwm_;
};

}  // namespace drivers
