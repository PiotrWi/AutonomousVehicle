#pragma once

#include <string>

class IMessageHandler
{
public:
    virtual void handle(const std::string& message) = 0;
    virtual std::string getPrefix() = 0;
    virtual void clear() = 0;
};