#pragma once

#include <vector>
#include <string>
#include "SequenceVerifier.hpp"

namespace pwm_sequences
{

const std::vector<std::string> pwmShallBeExported
{
    std::string{"open fd=@{exportFD${pwmChannel}}, loc=/sys/class/pwm/pwmchip0/export"},
    std::string{"write fd=${exportFD${pwmChannel}}, val=${pwmChannel}"},
    std::string{"close fd=${exportFD${pwmChannel}}"}
};

const std::vector<std::string> pwmPeriodShallBeSet
{
    std::string{"open fd=@{periodFD${pwmChannel}}, loc=/sys/class/pwm/pwmchip0/pwm${pwmChannel}/period"},
    std::string{"write fd=${periodFD${pwmChannel}}, val=10000000"},
    std::string{"close fd=${periodFD${pwmChannel}}"}
};


const std::vector<std::string> pwmDutyCycleShallBeinitializedAs0
{
    std::string {"open fd=@{dutyCycleFd${pwmChannel}}, loc=/sys/class/pwm/pwmchip0/pwm${pwmChannel}/duty_cycle"},
    std::string {"write fd=${dutyCycleFd${pwmChannel}}, val=0"},
    std::string {"close fd=${dutyCycleFd${pwmChannel}}"}
};

const std::vector<std::string> pwmShallBeEnabled
{
    std::string {"open fd=@{enableFD${pwmChannel}}, loc=/sys/class/pwm/pwmchip0/pwm${pwmChannel}/enable"},
    std::string {"write fd=${enableFD${pwmChannel}}, val=1"},
    std::string {"close fd=${enableFD${pwmChannel}}"}
};

const std::vector<std::string> pwmShallBeDisabled
{
    std::string {"open fd=@{disableFD${pwmChannel}}, loc=/sys/class/pwm/pwmchip0/pwm${pwmChannel}/enable"},
    std::string {"write fd=${disableFD${pwmChannel}}, val=0"},
    std::string {"close fd=${disableFD${pwmChannel}}"}
};

const std::vector<std::string> pwmShallBeUnexported
{
    std::string{"open fd=@{unexportFD${pwmChannel}}, loc=/sys/class/pwm/pwmchip0/unexport"},
    std::string{"write fd=${unexportFD${pwmChannel}}, val=${pwmChannel}"},
    std::string{"close fd=${unexportFD${pwmChannel}}"}
};

const std::vector<std::string> pwmShallSetDuty10p
{
    std::string {"write fd=@{dutyCycleFd${pwmChannel}}, val=1000000"},
};

void pushInitSequence(std::vector<std::vector<std::string>> &expectationsVector, const std::string& channelStr);
void pushUninitializeSequence(std::vector<std::vector<std::string>> &expectationsVector, const std::string& channelStr);
void pushPwmShallSetDuty10p(std::vector<std::vector<std::string>> &expectationsVector, const std::string& channelStr);

}  // namespace pwm_sequences
