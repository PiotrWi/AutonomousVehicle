#pragma once

#include <string>

#include "AccessPoint.hpp"

namespace networking
{

class MessageSender
{
public:
    explicit MessageSender(AccessPoint& ap);
    void send(const std::string& );
private:
    AccessPoint& ap_;
};

}  // namespace networking
