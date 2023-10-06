#include "CurrentTime.hpp"

#include <chrono>
#include <ctime>
#include <sstream>

std::string getCurrentTime()
{
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* localTime = std::localtime(&currentTime);

    std::stringstream ss;
    ss << localTime->tm_year << "-" << localTime->tm_mon << "-" << localTime->tm_mday
        << "_" << localTime->tm_hour << ":" << localTime->tm_min;
    return ss.str();
}
