#pragma once

#include "VehicleDriver/Drivers/Helpers/SysHelper.hpp"

namespace drivers
{

extern const char* GpioLocation;
extern const char* GpioExportLocation;
extern const char* GpioUnexportLocation;

template <const char* dir>
class GpioDriverBase
{
public:
    explicit GpioDriverBase(int pinNr)
            : pinNr_(pinNr)
              , isInitialized_(false)
    {

    }
    void init();
    void deinitialize();
protected:
    const int pinNr_;
    bool isInitialized_;
    FDRaiiWrapper fd_;
};

template <const char* dir>
void GpioDriverBase<dir>::init()
{
    isInitialized_ = true;

    auto pinStr = std::to_string(pinNr_);
    SysfsHelper::writeToSys(GpioExportLocation, pinStr);

    auto directionLoc = GpioLocation + std::string("/gpio") + pinStr + "/direction";
    SysfsHelper::writeToSys(directionLoc.c_str(), std::string(dir));
}

template <const char* dir>
void GpioDriverBase<dir>::deinitialize()
{
    if (not isInitialized_)
    {
        return;
    }

    auto pinStr = std::to_string(pinNr_);
    SysfsHelper::writeToSys(GpioUnexportLocation, pinStr);
    fd_.~FDRaiiWrapper();

    isInitialized_ = false;
}

}  // namespace drivers