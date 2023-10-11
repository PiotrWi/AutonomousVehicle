#pragma once

#include "MotorsDriver.hpp"
#include "GpioDriver.hpp"
#include "PwmDriver.hpp"
#include <stdexcept>

struct SpeedOutOfRange : public std::logic_error
{
public:
    SpeedOutOfRange()
            : std::logic_error("Speed out of range. It shall be in integer in range: <-100, 100>.") {}
};

void validateSpeed(int motorSpeed);

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
