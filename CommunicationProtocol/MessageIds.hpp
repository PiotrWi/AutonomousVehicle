#pragma once

#include <string>
#include <stdexcept>

struct MessageIdNotFound : public std::logic_error
{
    MessageIdNotFound(std::string protoClassName)
        : std::logic_error("MessageId not found for: " + protoClassName + ". Possibly You forgot to add it to MessageIds class.")
    {}
};

unsigned int getMsgId(const std::string&);