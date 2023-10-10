#include "AppConfig.hpp"

const char* CameraDumpDir = "/home/pioter/tmp";
//const char* CameraDumpDir = "/home/pi/tmp";

std::string AppConfig::getCameraDumpDirectory() const
{
    return std::string(CameraDumpDir);
}
