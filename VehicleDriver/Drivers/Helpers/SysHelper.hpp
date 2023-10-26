#pragma once

#include <string>

#include "FDRaiiWrapper.hpp"

class SysfsHelper
{
public:
    static FDRaiiWrapper openToRead(const char* loc);
    static std::string readFromSys(FDRaiiWrapper&);

    static FDRaiiWrapper openToWrite(const char* loc);
    static void writeToSys(const char* loc, const std::string & value);
    static void writeToSys(FDRaiiWrapper&, const std::string & value);

    static FDRaiiWrapper openToRW(const char* loc);
};
