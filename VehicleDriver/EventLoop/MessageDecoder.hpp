#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include "Event.hpp"

class NotHandledMessage : public std::logic_error
{
public:
    NotHandledMessage(std::string message);
};

Event decode(std::string message);
