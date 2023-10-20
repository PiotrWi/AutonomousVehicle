#include "MessageIds.hpp"

#include <map>

unsigned int getMsgId(const std::string& name)
{
    static std::map<std::string, unsigned int> nameToId
    {
        {"SetSpeed", 1},
        {"CurrentRequestedSpeed", 2},
        {"PublishImage", 3},
    };
    auto it = nameToId.find(name);
    if (it == nameToId.end())
    {
        throw MessageIdNotFound(name);
    }
    return it->second;
}