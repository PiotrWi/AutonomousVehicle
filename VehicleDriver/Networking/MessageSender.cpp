#include "MessageSender.hpp"

namespace networking
{

MessageSender::MessageSender(AccessPoint &ap)
    : ap_(ap)
{
}

void MessageSender::send(const std::string &message)
{
    ap_.send(message);
}

}  // namespace networking
