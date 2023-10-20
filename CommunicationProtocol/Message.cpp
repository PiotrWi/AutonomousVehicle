#include "Message.hpp"

#include <sstream>

#include <boost/format.hpp>

#include <Tools/StringAlgorithms.hpp>
#include "MessageFormat.hpp"

std::vector<Message> serializeToMessage(unsigned int messageId, std::string&& payload);

static unsigned int sequenceId = 0;

std::string to_string(const Message& message)
{
    if (message.sequenceInformation)
    {
        auto messageFormat = boost::format (sequenceMessageFormat.str);
        auto sequence = "(" + std::to_string(message.sequenceInformation->orderInSequence)  + "/"
                        + std::to_string(message.sequenceInformation->messagesInSequence) + ")";
        return (messageFormat % message.SequenceId
                              % message.messageType
                              % sequence
                              % message.payloadLength
                              % message.payload).str();
    }
    auto messageFormat = boost::format (simpleMessageFormat.str);
    return (messageFormat % message.SequenceId
            % message.messageType
            % message.payloadLength
            % message.payload).str();
}

std::vector<std::string> serializeToString(unsigned int messageId, std::string &&payload)
{
    std::vector<std::string> strMessages;
    std::vector<Message> messages = serializeToMessage(messageId, std::move(payload));

    std::transform(messages.begin(), messages.end(), std::back_inserter(strMessages), to_string);
    return strMessages;
}

unsigned int calculateMessagesNeeded(std::size_t payloadSize)
{
    auto howManyMessagesNeeded = payloadSize / PayloadMaxLen;
    auto reminder = (payloadSize % PayloadMaxLen);
    if (reminder)
    {
        howManyMessagesNeeded += 1;
    }
    std::size_t emtpyMessageSize = 1u;
    return std::max(emtpyMessageSize, howManyMessagesNeeded);
}

std::vector<Message> serializeToMessage(unsigned int messageId, std::string&& payload)
{
    std::vector<Message> messages;
    ++sequenceId;

    auto howManyMessagesNeeded = calculateMessagesNeeded(payload.size());
    for (unsigned int i=0; i < howManyMessagesNeeded; ++i)
    {
        Message m;
        m.SequenceId = sequenceId;
        m.messageType = messageId;
        if (howManyMessagesNeeded > 1)
        {
            m.sequenceInformation = SequenceInformation(i + 1, howManyMessagesNeeded);
        }
        if (i + 1 != howManyMessagesNeeded)
        {
            m.payloadLength = PayloadMaxLen;
            m.payload = payload.substr(PayloadMaxLen*i, PayloadMaxLen);
        }
        else
        {
            auto reminder = payload.size() - i * PayloadMaxLen;
            m.payloadLength = reminder;
            m.payload = payload.substr(PayloadMaxLen*i, reminder);
        }

        messages.push_back(m);
    }
    return messages;
}

std::optional<std::tuple<Message, BytesConsumed>> to_message(const std::string& messageStr)
{
    auto payloadStrPos = messageStr.find(PayloadStr);
    if (payloadStrPos == std::string::npos)
    {
        return {};
    }

    std::stringstream ss(messageStr);
    std::string key;
    Message m{};
    ss >> key >> m.SequenceId;
    ss >> key >> m.messageType;
    ss >> key;
    if (key == SequenceStr)
    {
        SequenceInformation si;
        ss >> key;
        key = tools::ltrim(key,'(');
        key = tools::rtrim(key,')');
        auto parts = tools::splitAndTrim(key, '/');
        si.orderInSequence = std::stoi(parts[0]);
        si.messagesInSequence = std::stoi(parts[1]);
        m.sequenceInformation = si;
        ss >> key;
    }
    ss >> m.payloadLength;

    auto payloadPos = payloadStrPos + std::string(PayloadStr).size() + 1;
    if (messageStr.size() < m.payloadLength + payloadPos)
    {
        return {};
    }

    m.payload = messageStr.substr(payloadPos, m.payloadLength);

    return std::make_tuple(m, payloadPos + m.payloadLength);
}
