#include <gtest/gtest.h>

#include "Tools/Checksum.hpp"

TEST(Checksum, shallBeCorrectlyCalculatedForSimpleArray)
{
    std::array<unsigned char, 4> array{1, 2, 3 ,4};
    auto crc = calculateChecksum(array.begin(), array.end());
    ASSERT_EQ(crc, 10);
}

TEST(Checksum, shallModuo1000Output)
{
    std::array<unsigned char, 10> array{101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
    auto crc = calculateChecksum(array.begin(), array.end());
    ASSERT_EQ(crc, 55);
}

TEST(Checksum, shallCalculateFromString)
{
    std::string str("aA7C3"); // 97 65 55 67 51
    auto crc = calculateChecksum(str.begin(), str.end());
    ASSERT_EQ(crc, 335);
}

TEST(Checksum, shallValiateCrc)
{
    std::string str("CRC: 335 PAYLOAD: aA7C3\n"); // 97 65 55 67 51

    ASSERT_TRUE(checkPayloadChecksum(str));
}

