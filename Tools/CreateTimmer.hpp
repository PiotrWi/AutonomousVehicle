#pragma once

#include <functional>

namespace tools
{

// TODO: Right now it supports just one instance of timmer. To be redesigned once needed.
int createRepeatingTimer(int microseconds, std::function<void()> callback);

}  // namespace tools
