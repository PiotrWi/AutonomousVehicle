#include "AppConfig.hpp"

const char* CameraDumpDir = "/home/pioter/tmp";
//const char* CameraDumpDir = "/home/pi/tmp";

std::string AppConfig::getCameraDumpDirectory()
{
    return std::string(CameraDumpDir);
}
