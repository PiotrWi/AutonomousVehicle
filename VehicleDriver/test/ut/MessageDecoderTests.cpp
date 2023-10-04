#include <EventLoop/MessageDecoder.hpp>

#include <string>

#include <gtest/gtest.h>

#include "EventLoop/GuiSpeedRequest.hpp"

using namespace std;


TEST(MessageDecoder, shallDecodeGuiSpeedRequest)
{
    const int givenLeftSpeed = 10;
    const int givenRightSpeed = 20;
    auto message = "Set speed: "s + std::to_string(givenLeftSpeed) + " " + std::to_string(givenRightSpeed) + "\n";

    auto event = decode(message);

    auto* specificEvent = event.get<GuiSpeedRequest>();
    ASSERT_EQ(specificEvent->leftWheel_, givenLeftSpeed);
    ASSERT_EQ(specificEvent->rightWheel_, givenRightSpeed);
}

TEST(MessageDecoder, shallDecodeGuiSpeedRequestWithNegativeNumbers)
{
    const int givenLeftSpeed = -10;
    const int givenRightSpeed = -20;
    auto message = "Set speed: "s + std::to_string(givenLeftSpeed) + " " + std::to_string(givenRightSpeed) + "\n";

    auto event = decode(message);

    auto* specificEvent = event.get<GuiSpeedRequest>();
    ASSERT_EQ(specificEvent->leftWheel_, givenLeftSpeed);
    ASSERT_EQ(specificEvent->rightWheel_, givenRightSpeed);
}