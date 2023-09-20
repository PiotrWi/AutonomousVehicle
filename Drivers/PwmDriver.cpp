#include "PwmDriver.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <string>

#include "SysHelper.hpp"

namespace
{

const char* PwmLocation = "/sys/class/pwm/pwmchip0";
const char* PwmExportLocation = "/sys/class/pwm/pwmchip0/export";
const char* PwmUnexportLocation = "/sys/class/pwm/pwmchip0/unexport";
const int defaultPeriod = 10000000;

}  // namespace

namespace drivers
{

using namespace std;

PwmDriver::PwmDriver(int channel)
    : channel_(channel)
    , isInitialized_(false)
{
}

void PwmDriver::init()
{
    isInitialized_ = true;

    auto channelStr = std::to_string(channel_);
    SysfsHelper::writeToSys(PwmExportLocation, channelStr);

    auto currentChannelLocation = PwmLocation + "/pwm"s + channelStr;
    auto periodLocation = currentChannelLocation + "/period";
    SysfsHelper::writeToSys(periodLocation.c_str(), std::to_string(defaultPeriod));

    auto valueLoc = currentChannelLocation + "/duty_cycle";
    fd_ = SysfsHelper::openToWrite(valueLoc.c_str());
    SysfsHelper::writeToSys(fd_, "0"s);

    auto enableLoc = currentChannelLocation + "/enable";
    SysfsHelper::writeToSys(enableLoc.c_str(), "1"s);
}

void PwmDriver::deinitialize()
{
    if (not isInitialized_) return;
    auto channelStr = std::to_string(channel_);
    auto currentChannelLocation = PwmLocation + "/pwm"s + channelStr;
    auto enableLoc = currentChannelLocation + "/enable";
    SysfsHelper::writeToSys(enableLoc.c_str(), std::string("0"));

    SysfsHelper::writeToSys(PwmUnexportLocation, channelStr);

    fd_.~FDRaiiWrapper();
    isInitialized_ = false;
}

void PwmDriver::set(unsigned int fill)
{
    auto value = std::to_string(fill * (defaultPeriod / 100));
    SysfsHelper::writeToSys(fd_, value);
}

PwmDriver::~PwmDriver()
{
    deinitialize();
}

}  // drivers