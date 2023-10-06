#pragma once

namespace components
{

struct Component
{
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Component() = default;
};

}  // namespace components
