#include "AppConfig.hpp"

namespace
{

// TODO(to be moved to file)
const std::string homeDir = "/home/pioter";
const std::string DumpDirectory = homeDir + "/tmp";
const std::string LeftCoefficientFileLoc = homeDir + "/proj/AuthonomousVehicle/VehicleDriver/Data/instrincts_left640x480.xml";
const std::string RightCoefficientFileLoc = homeDir + "/proj/AuthonomousVehicle/VehicleDriver/Data/instrincts_right640x480.xml";
const int cameraFps = 10;
const int cameraWidth = 640;
const int cameraHeight = 480;

}  // namespace

std::string AppConfig::getDumpDirectory() const
{
    return { DumpDirectory };
}

std::string AppConfig::getLeftCoefficientFileLoc() const
{
    return { LeftCoefficientFileLoc };
}

std::string AppConfig::getRightCoefficientFileLoc() const
{
    return { RightCoefficientFileLoc };
}

int AppConfig::getCameraFps() const
{
    return cameraFps;
}

int AppConfig::getCameraWidth() const
{
    return cameraWidth;
}

int AppConfig::getCameraHeight() const
{
    return cameraHeight;
}

