#include "MessageSender.hpp"

namespace networking
{

MessageSender::MessageSender(AccessPoint &ap)
    : ap_(ap)
{
}

void MessageSender::send(std::string&& message)
{
    ap_.send(std::move(message));
}

}  // namespace networking
