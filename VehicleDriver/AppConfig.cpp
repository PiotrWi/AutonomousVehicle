#include "AppConfig.hpp"

namespace
{

// TODO(to be moved to file)
const std::string homeDir = "/home/pioter";
const std::string CameraDumpDir = homeDir + "/tmp";
const std::string LeftCoefficientFileLoc = homeDir + "/proj/AuthonomousVehicle/VehicleDriver/Data/instrincts_left.xml";
const std::string RightCoefficientFileLoc = homeDir + "/proj/AuthonomousVehicle/VehicleDriver/Data/instrincts_right.xml";
const int cameraFps = 10;
const int cameraWidth = 320;
const int cameraHeight = 240;

}  // namespace

std::string AppConfig::getCameraDumpDirectory() const
{
    return { CameraDumpDir };
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
