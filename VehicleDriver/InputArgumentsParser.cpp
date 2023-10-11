#include "InputArgumentsParser.hpp"

#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include <Components/Component.hpp>
#include <Components/VideoProccessingComponent.hpp>
#include <Components/CameraProcessingComponent.hpp>
#include <Components/MotorTestComponents.hpp>
#include <Components/RobotComponent.hpp>
#include <Components/CalibrationComponent.hpp>

#include <ImageProcessing/PipelineFactory.hpp>

// Few examples how to run:
//   ./Autonomous_vehicle --video_processing --input solidYellowLeft.mp4
//   ./Autonomous_vehicle --camera_processing_component
//   ./Autonomous_vehicle --motor_test_component
//   ./Autonomous_vehicle --robot_component
//   ./Autonomous_vehicle --calibrate_component --input directory_with_calibration_data


class ParsingError : public std::runtime_error { public: ParsingError(); };
ParsingError::ParsingError() : std::runtime_error("Parsing error.") {}

auto getOptionsDescriptions()
{
    boost::program_options::options_description description("Allowed options:");
    description.add_options()
        ("help", "shows this message")
        ("video_processing", "process video file")
        ("input", boost::program_options::value<std::string>(), "provides an input parameter")
        ("camera_processing_component", "process data from camera")
        ("motor_test_component", "Allow user to set speed on the motors to test it.")
        ("robot_component", "Runs application to control robot")
        ("calibrate_component", "Utility to calibrate camera.");
    return description;
}

void printHelp(const boost::program_options::options_description& desc)
{
    std::cout << desc << std::endl;
    std::cout << std::endl;
    std::cout << "If you like to process already collected movie, please use: " << std::endl << "./Autonomous_vehicle --video_processing --input [filename]";
    std::cout << "If you like to proccess data from camera please use: " << std::endl << "./Autonomous_vehicle --camera_processing_component";
    std::cout << "If you like to test motors: " << std::endl << "./Autonomous_vehicle --motor_test_component";
    std::cout << "If you like to setup vehicle: " << std::endl << "./Autonomous_vehicle --robot_component";
}

std::unique_ptr<components::Component> createVideoProcessingComponent(const boost::program_options::variables_map& vm)
{
    if (not vm.contains("input")) throw ParsingError();

    return components::createVideoProcessingComponent(vm["input"].as<std::string>());
}

std::unique_ptr<components::Component> createCalibratingComponent(const boost::program_options::variables_map& vm)
{
    if (not vm.contains("input")) throw ParsingError();
    auto input = vm["input"].as<std::string>();
    return components::createCalibrationComponent(std::move(input));
}

void createComponentsBasedOnParserInput(int argc, char** argv, Application& application)
{
    auto desc = getOptionsDescriptions();
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, getOptionsDescriptions()), vm);
    boost::program_options::notify(vm);

    try
    {
        if (vm.count("help"))
        {
            printHelp(desc);
        }
        if (vm.count("video_processing"))
        {
            application.addComponent(createVideoProcessingComponent(vm));
        }
        if (vm.count("camera_processing_component"))
        {
            auto pipeline = image_processing::createDualCameraPreview();
            application.addComponent(components::createCameraProcessingComponent(std::move(pipeline)));
        }
        if (vm.count("motor_test_component"))
        {
            application.addComponent(components::createMotorTestComponent());
        }
        if (vm.count("calibrate_component"))
        {
            application.addComponent(createCalibratingComponent(vm));
        }
        if (vm.count("robot_component"))
        {
            application.addComponent(components::createRobotComponent(application.getApplicationContext()));
            auto pipeline = image_processing::createParallelCorrectedDualCameraPublish(application.getApplicationContext().messageSender_);
            application.addComponent(components::createCameraProcessingComponent(std::move(pipeline)));
        }
    }
    catch (const ParsingError& ex)
    {
        printHelp(desc);
        return;
    }
    if (not application.isValid())
    {
        printHelp(desc);
    }
}
