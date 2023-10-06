#pragma once

#include "Component.hpp"

#include <memory>

#include "Drivers/MotorsDriver.hpp"

namespace components
{

class MotorTestComponents : public Component
{
    void start() override;
    void stop() override;
private:
    drivers::MotorsDrivers driver_;
};

std::unique_ptr<Component> createMotorTestComponent();

} // components
