#include <gtest/gtest.h>

#include <string>

#include <Drivers/GpioDriver.hpp>

#include "SysfsTestUtils/GpioSequences.hpp"
#include "SysfsTestUtils/SysFsDriverBase.hpp"


using namespace std;
using namespace gpio_sentences;

namespace
{

class GpioDriverShould : public SysFsDriverBase{};

}  // namespace


TEST_F(GpioDriverShould, shallInitAndDeinit)
{
    pushInitSequence(expectationsVector_, "1"s);
    pushUninitializeSequence(expectationsVector_, "1"s);

    {
        drivers::GpioOutputDriver sut(1);
        sut.init();
    }

    verify();
}

TEST_F(GpioDriverShould, shallBeAbleToSetValues)
{
    pushInitSequence(expectationsVector_, "1"s);
    pushHighLowSequence(expectationsVector_, "1"s);
    pushUninitializeSequence(expectationsVector_, "1"s);

    {
        drivers::GpioOutputDriver sut(1);
        sut.init();
        sut.setHigh();
        sut.setLow();
    }

    verify();
}

TEST_F(GpioDriverShould, shallWorkFor2Pins)
{
    pushInitSequence(expectationsVector_, "1"s);
    pushInitSequence(expectationsVector_, "26"s);
    pushHighLowSequence(expectationsVector_, "1"s);
    pushHighLowSequence(expectationsVector_, "26"s);

    pushUninitializeSequence(expectationsVector_, "26"s);
    pushUninitializeSequence(expectationsVector_, "1"s);

    {
        drivers::GpioOutputDriver sut(1);
        drivers::GpioOutputDriver sut2(26);
        sut.init();
        sut2.init();

        sut.setHigh();
        sut2.setHigh();

        sut.setLow();
        sut2.setLow();
    }

    verify();
}