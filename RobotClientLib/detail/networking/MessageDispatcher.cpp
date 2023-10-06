#include "MessageDispatcher.hpp"

void MessageDispatcher::dispatchMessage(const std::string &message)
{
    for (auto&& [prefix, handler] : clients_)
    {
        if(message.starts_with(prefix))
        {
            handler(message);
        }
    }
}

void MessageDispatcher::subscribeFor(const std::string& prefix, std::function<void(std::string)> callback)
{
    clients_.emplace_back(std::make_pair(prefix, callback));
}
