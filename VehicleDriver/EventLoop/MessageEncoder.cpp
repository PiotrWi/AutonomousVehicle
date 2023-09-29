#include "MessageEncoder.hpp"

using namespace std;

std::string createCurrentRequestedSpeed(int leftWheel, int rightWheel)
{
    return "CurrentRequestedSpeed: "s + std::to_string(leftWheel) + " "s + std::to_string(rightWheel);
}
