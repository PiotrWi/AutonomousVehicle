#include "EncodersDriver.hpp"

namespace drivers
{

EncoderDriver::EncoderDriver(unsigned int c1Pin, unsigned int c2Pin)
    : c1PortGpio_(c1Pin)
    , c2PortGpio_(c2Pin)
{
}

void EncoderDriver::init(epoll_reactor::EpollReactor & epollReactor,
                         std::function<void(int)> onC1Change,
                         std::function<void(int)> onC2Change)
{
    c1PortGpio_.init(onC1Change);
    c2PortGpio_.init(onC2Change);

    epollReactor.registerEpollHandler(&c1PortGpio_);
    epollReactor.registerEpollHandler(&c2PortGpio_);

    onC1Change(c1PortGpio_.read());
    onC2Change(c2PortGpio_.read());
}

} // drivers