#pragma once

#include <optional>
#include <string>
#include <vector>
#include <tuple>
#include <SetSpeed.pb.h>

constexpr unsigned int HeaderMaxLen = 500;
constexpr unsigned int PayloadMaxLen = 64000;
constexpr unsigned int SingleMessageMaxLen = HeaderMaxLen + PayloadMaxLen;

using BytesConsumed = size_t;

struct SequenceInformation
{
    unsigned int orderInSequence;
    unsigned int messagesInSequence;
};

struct Message
{
    unsigned int SequenceId;
    unsigned int messageType;
    std::optional<SequenceInformation> sequenceInformation;

    unsigned int payloadLength;
    std::string payload;
};

/* Serialize single message to Single string with header and payload*/
std::string to_string(const Message& message);

/* Serialize single string with header and payload to single message.
 *
 * Return value:
 *      None: Value return can be empty if string contains just part of the message. Client shall attach next chunk to
 *          and try to deserialize it.
 *      arg<0>: Message - Single message deserialized,
 *      arg<1>: BytesConsumed - Not 0 if more than one message was serialized to chunk. Client shall take care about not
 *          consumed chunk and try to parse it once again.
 *
 * NOTE It may happen on network transmision that message is split to some smaller chunks or attach more than one message
 * to chunk.*/
std::optional<std::tuple<Message, BytesConsumed>> to_message(const std::string& message);

/* Serialize protobuf payload to set of string messages (EG: header + payload) in form to be sent trought network.
 *
 * NOTE: empty protobuf payload is still valid payload and at least single chunk shall be return.
 */
std::vector<std::string> serializeToString(unsigned int messageId, std::string&& payload);
