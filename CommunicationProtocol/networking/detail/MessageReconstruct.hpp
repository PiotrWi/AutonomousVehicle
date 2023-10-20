#pragma once

#include <string>
#include <vector>

#include <CommunicationProtocol/Message.hpp>

namespace networking
{

class MessageReconstruct
{
public:
    std::vector<Message> addChunk(const std::string &messageStr);

    void proccessBuffer();

private:
    std::string buffered_ = {};
    std::vector<Message> messages_ = {};
};

} // namespace networking