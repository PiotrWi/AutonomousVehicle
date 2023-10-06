#pragma once

#include <functional>
#include <vector>
#include <string>
#include <utility>

class MessageDispatcher
{
public:
    void dispatchMessage(const std::string& message);
    void subscribeFor(const std::string& prefix, std::function<void(std::string)>);
private:
    std::vector<std::pair<std::string, std::function<void(std::string)>>> clients_;
};
