#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include "Event.hpp"
#include <google/protobuf/message.h>

class NotHandledMessage : public std::logic_error
{
public:
    explicit NotHandledMessage(const std::string& message);
};


Event decode(const google::protobuf::Message& message);
