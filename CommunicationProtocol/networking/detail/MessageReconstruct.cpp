#include "MessageReconstruct.hpp"

namespace networking
{

std::vector<Message> MessageReconstruct::addChunk(const std::string &messageStr)
{
    buffered_ += messageStr;
    messages_ = {};

    proccessBuffer();

    return messages_;
}

void MessageReconstruct::proccessBuffer()
{
    while (true) {
        auto optMessage = to_message(buffered_);
        auto anyMessageReconstructed = optMessage.operator bool();
        if (not anyMessageReconstructed) {
            return;
        }
        auto [message, bytesConsumed] = *optMessage;
        messages_.push_back(message);
        buffered_ = buffered_.substr(bytesConsumed, buffered_.size());
    }
}

}  // namespace networking