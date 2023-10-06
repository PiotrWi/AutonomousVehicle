#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include "Event.hpp"

class NotHandledMessage : public std::logic_error
{
public:
    explicit NotHandledMessage(const std::string& message);
};

Event decode(const std::string& message);
