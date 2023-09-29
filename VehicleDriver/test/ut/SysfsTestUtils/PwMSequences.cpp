#include "PwmSequences.hpp"

namespace pwm_sequences
{

void pushInitSequence(std::vector<std::vector<std::string>> &expectationsVector, std::string channelStr)
{
    using namespace std;

    auto exportSequence = pwmShallBeExported;
    instantiate(exportSequence, "pwmChannel"s, channelStr);
    expectationsVector.push_back(exportSequence);

    auto periodSequence = pwmPeriodShallBeSet;
    instantiate(periodSequence, "pwmChannel"s, channelStr);
    expectationsVector.push_back(periodSequence);

    auto setDefaultDutyCycleSequence = pwmDutyCycleShallBeinitializedAs0;
    instantiate(setDefaultDutyCycleSequence, "pwmChannel"s, channelStr);
    expectationsVector.push_back(setDefaultDutyCycleSequence);

    auto enablePwn = pwmShallBeEnabled;
    instantiate(enablePwn, "pwmChannel"s, channelStr);
    expectationsVector.push_back(enablePwn);
}

void pushUninitializeSequence(std::vector<std::vector<std::string>> &expectationsVector, std::string channelStr)
{
    using namespace std;

    auto disableSequence = pwmShallBeDisabled;
    instantiate(disableSequence, "pwmChannel"s, channelStr);
    expectationsVector.push_back(disableSequence);
}

void pushPwmShallSetDuty10p(std::vector<std::vector<std::string>> &expectationsVector, std::string channelStr)
{
    using namespace std;

    auto dutyCycleSet = pwmShallSetDuty10p;
    instantiate(dutyCycleSet, "pwmChannel"s, channelStr);
    expectationsVector.push_back(dutyCycleSet);
};

}  // namespace pwm_sequences
