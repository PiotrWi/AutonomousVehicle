#pragma once

#include <string>

template <typename TProtoType>
class IMessageHandler
{
public:
    virtual void handle(const TProtoType& message) = 0;
    virtual void clear() = 0;
};