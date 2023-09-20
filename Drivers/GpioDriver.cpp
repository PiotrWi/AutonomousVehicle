#include "GpioDriver.hpp"

#include <string>

#include "SysHelper.hpp"

namespace
{

const char* GpioLocation = "/sys/class/gpio";
const char* GpioExportLocation = "/sys/class/gpio/export";
const char* GpioUnexportLocation = "/sys/class/gpio/unexport";

}  // namespace

namespace drivers
{

using namespace std;

GpioOutputDriver::GpioOutputDriver(int pinNr)
    : pinNr_(pinNr)
    , isInitialized_(false)
{
}

void GpioOutputDriver::init()
{
    isInitialized_ = true;

    auto pinStr = std::to_string(pinNr_);
    SysfsHelper::writeToSys(GpioExportLocation, pinStr);

    auto directionLoc = GpioLocation + "/gpio"s + pinStr + "/direction";
    SysfsHelper::writeToSys(directionLoc.c_str(), std::string("out"));

    auto valueLoc = GpioLocation + "/gpio"s + pinStr + "/value";

    fd_ = SysfsHelper::openToWrite(valueLoc.c_str());
    setLow();
}

void GpioOutputDriver::deinitialize()
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

void GpioOutputDriver::setHigh()
{
    SysfsHelper::writeToSys(fd_, "1"s);
}

void GpioOutputDriver::setLow()
{
    SysfsHelper::writeToSys(fd_, "0"s);
}

GpioOutputDriver::~GpioOutputDriver()
{
    deinitialize();
}

}  // drivers
