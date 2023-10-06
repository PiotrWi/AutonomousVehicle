#pragma once

#include <string>

class IMessageHandler
{
public:
    virtual void handle(const std::string& message) = 0;
    virtual std::string getPrefix() const = 0;
    virtual void clear() = 0;
};