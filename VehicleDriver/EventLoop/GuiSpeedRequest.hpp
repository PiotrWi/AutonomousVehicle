#pragma once

#include "EventIds.hpp"

struct GuiSpeedRequest
{
    int leftWheel_;
    int rightWheel_;
};

template<>
inline unsigned int getId<GuiSpeedRequest>()
{
    return GuiSpeedRequestId;
}
