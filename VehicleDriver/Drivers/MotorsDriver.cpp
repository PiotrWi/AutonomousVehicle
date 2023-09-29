#include "MotorsDriver.hpp"

namespace drivers
{

MotorsDrivers::MotorsDrivers()
    : phasePinLeftMotor_(6)
    , phasePinRightMotor_(5)
    , leftMotorPwm_(1)
    , rightMotorPwm_(0)
{
}

void MotorsDrivers::init()
{
    phasePinLeftMotor_.init();
    phasePinRightMotor_.init();
    leftMotorPwm_.init();
    rightMotorPwm_.init();
}

void MotorsDrivers::deinitialize()
{
    phasePinLeftMotor_.deinitialize();
    phasePinRightMotor_.deinitialize();
    leftMotorPwm_.deinitialize();
    rightMotorPwm_.deinitialize();
}

void MotorsDrivers::stop()
{
    leftMotorPwm_.set(0);
    rightMotorPwm_.set(0);
}

void MotorsDrivers::setSpeed(int leftMotor, int rightMotor)
{
    if (leftMotor > 0)
    {
        phasePinLeftMotor_.setHigh();
        leftMotorPwm_.set(leftMotor);
    }
    else
    {
        phasePinLeftMotor_.setLow();
        leftMotorPwm_.set(-1*leftMotor);
    }

    if (rightMotor > 0)
    {
        phasePinRightMotor_.setHigh();
        rightMotorPwm_.set(rightMotor);
    }
    else
    {
        phasePinRightMotor_.setLow();
        rightMotorPwm_.set(-1*rightMotor);
    }
}

MotorsDrivers::~MotorsDrivers()
{
    deinitialize();
}

}  // namespace drivers
