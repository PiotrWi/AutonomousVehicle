#include <gtest/gtest.h>

#include <type_traits>
#include <Message.hpp>

#include <SimpleProto.pb.h>
#include <SplitableProto.pb.h>

struct AnyValue {};

template<typename TArg>
bool operator==(TArg&&, const AnyValue&) { return true; }

struct AnySequenceIdMessage : public Message
{
    explicit AnySequenceIdMessage(Message m) : Message(m) {}
    AnyValue SequenceId;
};

struct AnySequenceIdAndPayload : public Message
{
    explicit AnySequenceIdAndPayload(Message m) : Message(m) {}
    AnyValue SequenceId;
    AnyValue payloadLength;
    AnyValue payload;
};

bool operator==(const SequenceInformation &lhs, const SequenceInformation &rhs)
{
    return lhs.orderInSequence == rhs.orderInSequence
           && lhs.messagesInSequence == rhs.messagesInSequence;
}

bool operator==(const Message &lhs, const Message &rhs)
{
    return lhs.SequenceId == rhs.SequenceId
           && lhs.messageType == rhs.messageType
           && lhs.sequenceInformation == rhs.sequenceInformation
           && lhs.payloadLength == rhs.payloadLength
           && lhs.payload == rhs.payload;
}

template <typename TComparableToMessage>
requires std::derived_from<TComparableToMessage, Message>
bool operator==(const Message &lhs, const TComparableToMessage &rhs)
{
    return lhs.SequenceId == rhs.SequenceId
           && lhs.messageType == rhs.messageType
           && lhs.sequenceInformation == rhs.sequenceInformation
           && lhs.payloadLength == rhs.payloadLength
           && lhs.payload == rhs.payload;
}

template <typename T>
concept ProtoBufMessage = std::derived_from<T, google::protobuf::Message>;

template <typename TProtoMessage> requires ProtoBufMessage<TProtoMessage>
std::string serializeProtobuf(const TProtoMessage &sp)
{
    std::string protobuffPayload;
    sp.SerializeToString(&protobuffPayload);
    return protobuffPayload;
}

template <typename TProtoMessage> requires ProtoBufMessage<TProtoMessage>
TProtoMessage deserializeProtobuf(std::string s)
{
    TProtoMessage sp;
    sp.ParseFromString(s);
    return sp;
}

TEST(NoPayloadMessageShall, beConvertableToStringAndReverse)
{
    unsigned sequenceID = 4;
    unsigned messageType = 2;
    std::string noPayload;
    auto givenMessage = Message (
        sequenceID, messageType, {}, noPayload.size(), noPayload
    );

    auto messageStr = to_string(givenMessage);

    ASSERT_EQ(messageStr, "SeqId: 4 MsgType: 2 PayloadLength: 0 PAYLOAD: ");

    auto deserializedMessage = to_message(messageStr);

    ASSERT_TRUE(deserializedMessage);
    ASSERT_EQ(givenMessage, std::get<Message>(*deserializedMessage));
}

TEST(ShortMessageShall, beConvertableToStringAndReverse)
{
    unsigned sequenceID = 4;
    unsigned messageType = 2;
    std::string payload = "SomePayload";
    auto givenMessage = Message (
            sequenceID, messageType, {}, payload.size(), payload
    );

    auto messageStr = to_string(givenMessage);
    ASSERT_EQ(messageStr, "SeqId: 4 MsgType: 2 PayloadLength: 11 PAYLOAD: SomePayload");

    auto deserializedMessage = to_message(messageStr);

    ASSERT_TRUE(deserializedMessage);
    ASSERT_EQ(givenMessage, std::get<Message>(*deserializedMessage));
}

TEST(ShortMessageShall, notBeRestoredIfPayloadIsNotFullyAvailable)
{
    unsigned sequenceID = 4;
    unsigned messageType = 2;
    std::string payload = "Some";
    auto givenMessage = Message (
            sequenceID, messageType, {}, 11, payload
    );

    auto messageStr = to_string(givenMessage);
    ASSERT_EQ(messageStr, "SeqId: 4 MsgType: 2 PayloadLength: 11 PAYLOAD: Some");

    auto deserializedMessage = to_message(messageStr);

    ASSERT_FALSE(deserializedMessage);
}

TEST(SequencedMessageShall, beConvertableToStringAndReverse)
{
    unsigned sequenceID = 4;
    unsigned messageType = 2;
    SequenceInformation si {2, 12};
    std::string payload = "SomePayload";
    auto givenMessage = Message (
            sequenceID, messageType, si, payload.size(), payload
    );

    auto messageStr = to_string(givenMessage);
    ASSERT_EQ(messageStr, "SeqId: 4 MsgType: 2 Sequence: (2/12) PayloadLength: 11 PAYLOAD: SomePayload");

    auto deserializedMessage = to_message(messageStr);

    ASSERT_TRUE(deserializedMessage);
    ASSERT_EQ(givenMessage, std::get<Message>(*deserializedMessage));
}

TEST(EmptyProtobuffPayloadShall, beSerializedToSingleMessage)
{
    unsigned int irrelevantSequenceId = 1;
    unsigned int FakeId = 0;
    AnySequenceIdMessage expectedMessage{Message{irrelevantSequenceId, FakeId, {}, 0, {}}};

    SimpleProto sp;
    sp.set_value1(0);
    sp.set_value2(0);

    auto messagesStrSet = serializeToString(FakeId, serializeProtobuf(sp));
    ASSERT_EQ(messagesStrSet.size(), 1u);

    auto deserializedMessage = to_message(messagesStrSet[0]);
    ASSERT_EQ(expectedMessage, std::get<Message>(*deserializedMessage));
}

TEST(ShortProtobuffPayloadShall, beSerializedToSingleMessage)
{
    unsigned int irrelevantSequenceId = 1;
    unsigned int FakeId = 0;
    AnySequenceIdAndPayload expectedMessage{Message{irrelevantSequenceId, FakeId, {}, 0, {}}};

    SimpleProto sp;
    sp.set_value1(1);
    sp.set_value2(2);

    auto messagesStrSet = serializeToString(FakeId, serializeProtobuf(sp));
    ASSERT_EQ(messagesStrSet.size(), 1u);

    auto deserializedMessage = to_message(messagesStrSet[0]);
    ASSERT_EQ(expectedMessage, std::get<Message>(*deserializedMessage));

    // TODO(PiotrWi): Verify payload
}

TEST(ShortProtobuffPayloadShall, notCrashOncePayloadIsBoostFormatAlike)
{
    unsigned int SequenceId = 1;
    unsigned int FakeId = 0;
    std::string payload = "%1% %2% %3% %4% %5% %6% %7%";

    Message message(SequenceId, FakeId, {}, payload.size(), payload);
    auto messageStr = to_string(message);
    ASSERT_EQ(messageStr, "SeqId: 1 MsgType: 0 PayloadLength: 27 PAYLOAD: %1% %2% %3% %4% %5% %6% %7%");
}

TEST(LongProtobuffPayloadShall, beSerializedToSingleMessage)
{
    unsigned int irrelevantSequenceId = 1;
    unsigned int FakeId = 0;

    std::string veryLongString;
    std::generate_n(std::back_inserter(veryLongString), 9000000, []{ return 'a'; });

    SplitableProto sp;
    sp.set_payload(veryLongString);

    auto messagesStrSet = serializeToString(FakeId, serializeProtobuf(sp));
    ASSERT_TRUE(messagesStrSet.size() == 141);

    std::string reconstructedProtobufPayload;
    for (auto i = 1u; i <= messagesStrSet.size(); ++i)
    {
        SequenceInformation si(i, messagesStrSet.size());
        AnySequenceIdAndPayload expectedMessage(Message{irrelevantSequenceId, FakeId, si, 0, {}});
        auto [deserializedMessage, bytesConsumed] = *to_message(messagesStrSet[i - 1]);
        ASSERT_EQ(expectedMessage, deserializedMessage);
        reconstructedProtobufPayload += deserializedMessage.payload;
    }
    auto reconstructedProto = deserializeProtobuf<SplitableProto>(reconstructedProtobufPayload);
    ASSERT_EQ(sp.payload(), reconstructedProto.payload());
}
