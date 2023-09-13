#pragma once

namespace components
{

struct Component
{
    virtual void start() = 0;

    virtual ~Component()
    {};
};

}  // namespace components
