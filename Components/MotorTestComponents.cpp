#include "MotorTestComponents.hpp"

#include <iostream>

#include <tools/StringAlgorithms.hpp>

namespace
{

struct SpeedOutOfRange : public std::logic_error
{
public:
    SpeedOutOfRange()
        : std::logic_error("Speed out of range. It shall be in integer in range: <-100, 100>.") {}
};

void validateSpeed(int motorSpeed)
{
    if ((motorSpeed > 100) | (motorSpeed < -100))
    {
        throw SpeedOutOfRange();
    }
}

}  // namespace

namespace components
{



void MotorTestComponents::start()
{
    std::cout << "Motor component test." << std::endl;
    std::cout << "Provide two numbers to console to setup given speed: LeftMotor[-100:100] RightMotor[-100:100]" << std::endl;
    std::cout << "provide q to exit program." << std::endl;

    std::string line;

    driver_.init();

    while (true)
    {
        std::getline(std::cin, line);
        if (line == "q")
        {
            std::cout << "exit" << std::endl;
            driver_.deinitialize();
            return;
        }
        try
        {
            auto givenSpeeds = splitAndTrim(line, ' ');
            auto leftMotorSpeed = std::stoi(givenSpeeds[0]);
            auto rightMotorSpeed = std::stoi(givenSpeeds[1]);

            validateSpeed(leftMotorSpeed);
            validateSpeed(rightMotorSpeed);

            driver_.setSpeed(leftMotorSpeed, rightMotorSpeed);
        }
        catch (const std::exception& ex)
        {
            std::cout << "Data in inpropper format" << std::endl;
            std::cout << "Error: " << ex.what() << std::endl;
            std::cout << "exiting" << std::endl;

            driver_.deinitialize();
            return;
        }
    }
}

std::unique_ptr<Component> createMotorTestComponent()
{
    return std::make_unique<MotorTestComponents>();
}

}  // components