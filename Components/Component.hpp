#pragma once

struct Component
{
    virtual void start() = 0;
    virtual ~Component() {};
};