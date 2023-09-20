#pragma once

#include <string>

#include "FDRaiiWrapper.hpp"

class SysfsHelper
{
public:
    static void writeToSys(const char* loc, const std::string & value);
    static FDRaiiWrapper openToWrite(const char* loc);
    static void writeToSys(FDRaiiWrapper&, const std::string & value);
};
