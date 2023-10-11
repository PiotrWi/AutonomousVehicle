#include "AppConfig.hpp"

namespace
{

std::string homeDir = "/home/pioter";
std::string CameraDumpDir = homeDir + "/tmp";
std::string LeftCoefficientFileLoc = homeDir + "/proj/AuthonomousVehicle/VehicleDriver/Data/instrincts_left.xml";
std::string RightCoefficientFileLoc = homeDir + "/proj/AuthonomousVehicle/VehicleDriver/Data/instrincts_right.xml";

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
