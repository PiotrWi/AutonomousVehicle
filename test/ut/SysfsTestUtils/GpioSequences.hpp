#pragma once

#include <string>
#include <vector>
#include "SequenceVerifier.hpp"

namespace gpio_sentences
{

const std::vector<std::string> pinShallBeExportedInSys =
        {
                std::string{"open fd=@{exportFD${pinNr}}, loc=/sys/class/gpio/export"},
                std::string{"write fd=${exportFD${pinNr}}, val=${pinNr}"},
                std::string{"close fd=${exportFD${pinNr}}"}
        };

const std::vector<std::string> directionShallBeSetAsOut =
        {
                std::string{"open fd=@{dirrectionFD${pinNr}}, loc=/sys/class/gpio/gpio${pinNr}/direction"},
                std::string{"write fd=${dirrectionFD${pinNr}}, val=out"},
                std::string{"close fd=${dirrectionFD${pinNr}}"}
        };

const std::vector<std::string> defaultValueShallBeSetToLow
        {
                std::string{"open fd=@{pinManipFD${pinNr}}, loc=/sys/class/gpio/gpio${pinNr}/value"},
                std::string{"write fd=${pinManipFD${pinNr}}, val=0"},
                std::string{"close fd=${pinManipFD${pinNr}}"}
        };

const std::vector<std::string> pinShallBeUnExportedInSys =
        {
                std::string{"open fd=@{unexportFD${pinNr}}, loc=/sys/class/gpio/unexport"},
                std::string{"write fd=${unexportFD${pinNr}}, val=${pinNr}"},
                std::string{"close fd=${unexportFD${pinNr}}"}
        };

const std::vector<std::string> pinShallBeSetToHigh
        {
                std::string{"write fd=@{pinManipFD${pinNr}}, val=1"},
        };
const std::vector<std::string> pinShallBeSetToLow
        {
                std::string{"write fd=@{pinManipFD${pinNr}}, val=0"},
        };

void pushInitSequence(std::vector<std::vector<std::string>> &expectationsVector, std::string pinStr);
void pushUninitializeSequence(std::vector<std::vector<std::string>> &expectationsVector, std::string pinStr);
void pushHighLowSequence(std::vector<std::vector<std::string>> &expectationsVector, std::string pinStr);

}  // namespace gpio_sentences
