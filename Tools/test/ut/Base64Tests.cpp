#include <gtest/gtest.h>
#include <Tools/Base64.hpp>

TEST(Base64, shallCodeEncode)
{
    std::vector<unsigned char> given{0, 1, 2};
    auto str =  Base64Encode(given);
    auto decoded = Base64Decode(str);

    ASSERT_EQ(given, decoded);
}

TEST(Base64, shallCodeEncodeOneSymbol)
{
    std::vector<unsigned char> given{222};
    auto str =  Base64Encode(given);
    auto decoded = Base64Decode(str);

    ASSERT_EQ(given, decoded);
}

TEST(Base64, shallCodeEncodeTwoSymbols)
{
    std::vector<unsigned char> given{222, 123};
    auto str =  Base64Encode(given);
    auto decoded = Base64Decode(str);

    ASSERT_EQ(given, decoded);
}

TEST(Base64, shallCodeEncodeAllUChars)
{
    std::vector<unsigned char> given;
    for (unsigned short i = 0; i <= 255; ++i)
    {
        given.push_back(i);
    }
    auto str =  Base64Encode(given);
    auto decoded = Base64Decode(str);

    ASSERT_EQ(given, decoded);
}
