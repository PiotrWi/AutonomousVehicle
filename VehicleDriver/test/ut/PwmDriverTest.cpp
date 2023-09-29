#include <gtest/gtest.h>

#include <string>

#include "VehicleDriver/Drivers/PwmDriver.hpp"

#include "VehicleDriver/test/ut/SysfsTestUtils/PwmSequences.hpp"
#include "VehicleDriver/test/ut/SysfsTestUtils/SysFsDriverBase.hpp"


using namespace std;
using namespace pwm_sequences;

class PwmDriverShould : public SysFsDriverBase{};

TEST_F(PwmDriverShould, beInitializedDeinitialized)
{
    pushInitSequence(expectationsVector_, "0"s);
    pushUninitializeSequence(expectationsVector_, "0"s);

    {
        drivers::PwmDriver sut(0);
        sut.init();
    }

    verify();
}

TEST_F(PwmDriverShould, setSomeDuty)
{
    pushInitSequence(expectationsVector_, "0"s);
    pushPwmShallSetDuty10p(expectationsVector_, "0"s);
    pushUninitializeSequence(expectationsVector_, "0"s);

    {
        drivers::PwmDriver sut(0);
        sut.init();
        sut.set(10);
    }

    verify();
}
