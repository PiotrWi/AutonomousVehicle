#include "MotorTestComponents.hpp"

#include <iostream>

#include "../../Tools/StringAlgorithms.hpp"

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
            auto givenSpeeds = tools::splitAndTrim(line, ' ');
            auto leftMotorSpeed = std::stoi(givenSpeeds[0]);
            auto rightMotorSpeed = std::stoi(givenSpeeds[1]);

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

void MotorTestComponents::stop()
{

}

std::unique_ptr<Component> createMotorTestComponent()
{
    return std::make_unique<MotorTestComponents>();
}

}  // components