#include "GpioSequences.hpp"

namespace gpio_sentences
{

void pushInitSequence(std::vector<std::vector<std::string>> &expectationsVector, std::string pinStr)
{
    using namespace std;

    auto exportSequence = pinShallBeExportedInSys;
    instantiate(exportSequence, "pinNr"s, pinStr);
    expectationsVector.push_back(exportSequence);

    auto directionSequence = directionShallBeSetAsOut;
    instantiate(directionSequence, "pinNr"s, pinStr);
    expectationsVector.push_back(directionSequence);

    auto setDefaultStateSequence = defaultValueShallBeSetToLow;
    instantiate(setDefaultStateSequence, "pinNr"s, pinStr);
    expectationsVector.push_back(setDefaultStateSequence);
}

void pushUninitializeSequence(std::vector<std::vector<std::string>> &expectationsVector, std::string pinStr)
{
    using namespace std;

    auto uninitializeSequence = pinShallBeUnExportedInSys;
    instantiate(uninitializeSequence, "pinNr"s, pinStr);
    expectationsVector.push_back(uninitializeSequence);
}

void pushHighLowSequence(std::vector<std::vector<std::string>> &expectationsVector, std::string pinStr)
{
    using namespace std;

    auto pinHighSequence = pinShallBeSetToHigh;
    instantiate(pinHighSequence, "pinNr"s, pinStr);
    expectationsVector.push_back(pinHighSequence);

    auto pinLowSequence = pinShallBeSetToLow;
    instantiate(pinLowSequence, "pinNr"s, pinStr);
    expectationsVector.push_back(pinLowSequence);
}

}  // namespace gpio_sentences
