#include "VehicleDriver/test/ut/SysfsTestUtils/SysFsDriverBase.hpp"

#include "VehicleDriver/Drivers/MotorsDriver.hpp"

#include "VehicleDriver/test/ut/SysfsTestUtils/GpioSequences.hpp"
#include "VehicleDriver/test/ut/SysfsTestUtils/PwmSequences.hpp"

class MotorDriverShould : public SysFsDriverBase {};

using namespace std;

TEST_F (MotorDriverShould, beInitializedDeinitialized)
{
    gpio_sentences::pushInitSequence(expectationsVector_, "6"s);
    gpio_sentences::pushInitSequence(expectationsVector_, "5"s);
    pwm_sequences::pushInitSequence(expectationsVector_, "1"s);
    pwm_sequences::pushInitSequence(expectationsVector_, "0"s);

    gpio_sentences::pushUninitializeSequence(expectationsVector_, "6"s);
    gpio_sentences::pushUninitializeSequence(expectationsVector_, "5"s);
    pwm_sequences::pushUninitializeSequence(expectationsVector_, "1"s);
    pwm_sequences::pushUninitializeSequence(expectationsVector_, "0"s);

    {
        drivers::MotorsDrivers sut;
        sut.init();
    }

    verify();
}
