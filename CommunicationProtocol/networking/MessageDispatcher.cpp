#include "MessageDispatcher.hpp"
#include "../Message.hpp"

namespace networking
{

void MessageDispatcher::dispatchMessage(const std::string& messageStr)
{
    auto completeMessages = buffer_.addChunk(messageStr);

    for (auto&& message : completeMessages)
    {
        if (message.sequenceInformation)
        {
            sequencedMessages_.push_back(message);
            if (message.sequenceInformation->messagesInSequence == sequencedMessages_.size())
            {
                std::string payload;
                for (auto&& p : sequencedMessages_)
                {
                    payload += std::move(p.payload);
                }
                sequencedMessages_.clear();
                dispatchToHandler(message.messageType, payload);
            }
        }
        else
        {
            dispatchToHandler(message.messageType, message.payload);
        }
    }
}

void MessageDispatcher::dispatchToHandler(unsigned int messageType, std::string &payload)
{
    auto handler = concreteMessageHandlers_[messageType];
    if (handler != nullptr)
    {
        handler->handle(std::move(payload));
    }
}

}