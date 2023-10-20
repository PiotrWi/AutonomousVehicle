#pragma once

#include <string>
#include <type_traits>
#include "../Message.hpp"
#include "../MessageIds.hpp"
#include <google/protobuf/message.h>

template <typename T>
concept ProtoBufMessage = std::derived_from<T, google::protobuf::Message>;

namespace networking
{

template<typename TAccessPointImplementation>
class MessageSender
{
public:
    explicit MessageSender(TAccessPointImplementation &ap) : ap_(ap)
    {}

    void send(unsigned int id, std::string &&payload)
    {
        auto messages = serializeToString(id, std::move(payload));
        ap_.send(std::move(messages));
    }

    template<class TProtoMessage> requires ProtoBufMessage<TProtoMessage>
    void send(TProtoMessage&& msg)
    {
        auto id = getMsgId(msg.GetTypeName());
        std::string payload;
        if (not msg.SerializeToString(&payload))
        {
            std::cerr << "MessageSender::send serrialization failure" << std::endl;
        }
        send(id, std::move(payload));
    }

private:
    TAccessPointImplementation &ap_;
};

}  // namespace networking
