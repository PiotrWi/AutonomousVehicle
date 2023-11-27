#include "GpioDriver.hpp"

#include <iostream>
#include <string>

#include "VehicleDriver/Drivers/Helpers/SysHelper.hpp"

namespace drivers
{

const char in[] = "in";
const char out[] = "out";

const char *GpioValueLocation = "/sys/class/gpio/export";

GpioInputDriver::GpioInputDriver(int pinNr)
    : GpioDriverBase<in>(pinNr)
{
}

void GpioInputDriver::init()
{
    GpioDriverBase::init();

    auto valueLoc = GpioLocation + std::string("/gpio") + std::to_string(this->pinNr_) + "/value";
    fd_ = SysfsHelper::openToRead(valueLoc.c_str());
}

GpioInputDriver::~GpioInputDriver()
{
    deinitialize();
}

int GpioInputDriver::read()
{
    auto val = SysfsHelper::readFromSys(fd_);

    std::cout << "GpioInputDriver[" << fd_.get() << "]:" << val << std::endl;  // TMP

    return std::stoi(val);
}

GpioOutputDriver::GpioOutputDriver(int pinNr)
    : GpioDriverBase<out>(pinNr)
{
}

void GpioOutputDriver::setHigh()
{
    SysfsHelper::writeToSys(fd_, std::string{"1"});
}

void GpioOutputDriver::setLow()
{
    SysfsHelper::writeToSys(fd_, std::string{"0"});
}

GpioOutputDriver::~GpioOutputDriver()
{
    deinitialize();
}

void GpioOutputDriver::init()
{
    GpioDriverBase::init();

    auto valueLoc = GpioLocation + std::string("/gpio") + std::to_string(this->pinNr_) + "/value";
    fd_ = SysfsHelper::openToWrite(valueLoc.c_str());
    setLow();
}

GpioInputDriverEpollHandler::GpioInputDriverEpollHandler(int pinNr)
        : GpioInputDriver(pinNr)
{
}

void GpioInputDriverEpollHandler::init(std::function<void(bool)> onChange)
{
    onChange_ = onChange;
    GpioDriverBase::init();
    initEdges();

    auto valueLoc = GpioLocation + std::string("/gpio") + std::to_string(this->pinNr_) + "/value";
    fd_ = SysfsHelper::openToRead(valueLoc.c_str());
}

void GpioInputDriverEpollHandler::initEdges()
{
    auto edgeLoc = GpioLocation + std::string("/gpio") + std::to_string(this->pinNr_) + "/edge";
    SysfsHelper::writeToSys(edgeLoc.c_str(), std::string {"both"});
}

std::vector<int> GpioInputDriverEpollHandler::getDescriptorsToObserve() const
{
    return {fd_.get()};
}

void GpioInputDriverEpollHandler::onAvailable(int)
{
    readEdges();
}

void GpioInputDriverEpollHandler::readEdges()
{
    auto newVal = read();
    if (onChange_)
    {
        onChange_(newVal);
    }
}

}  // drivers
