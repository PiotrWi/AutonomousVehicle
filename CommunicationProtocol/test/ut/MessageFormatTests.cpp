#include <gtest/gtest.h>

#include <MessageFormat.hpp>

TEST(MessageFormatShall, generateCorrectFormatForSimpleMessage)
{
    std::string s(simpleMessageFormat.str);
    ASSERT_EQ(s, "SeqId: %1% MsgType: %2% PayloadLength: %3% PAYLOAD: %4%");
}

TEST(MessageFormatShall, generateCorrectFormatForSequenceMessage)
{
    std::string s(sequenceMessageFormat.str);
    ASSERT_EQ(s, "SeqId: %1% MsgType: %2% Sequence: %3% PayloadLength: %4% PAYLOAD: %5%");
}
