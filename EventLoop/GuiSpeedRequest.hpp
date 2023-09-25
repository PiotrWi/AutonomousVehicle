#pragma once

#include "EventIds.hpp"

struct GuiSpeedRequest
{
    unsigned int leftWheel_;
    unsigned int rightWheel_;
};

template<>
inline unsigned int getId<GuiSpeedRequest>()
{
    return GuiSpeedRequestId;
}