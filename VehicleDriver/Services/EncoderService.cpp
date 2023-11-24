#include "EncoderService.hpp"

#include <AppConfig.hpp>
#include <chrono>
#include <functional>

#include <Tools/CurrentTime.hpp>

namespace services
{

EncoderService::EncoderService(drivers::epoll_reactor::EpollReactor &epollReactor)
    : epollReactor_(epollReactor)
    , leftEncoder_(19, 26)
    , rightEncoder_(16, 20)
    , measurementBegin_(std::chrono::steady_clock::now())
{
}

void EncoderService::initDumpFiles()
{
    auto dirBase = AppConfig::getInstance().getDumpDirectory();
    auto timeStr = getCurrentTime();

    get(Side::Left, EncoderPort::c1).dumpFile_.open(dirBase + "/leftC1" + timeStr);
    get(Side::Left, EncoderPort::c2).dumpFile_.open(dirBase + "/leftC2" + timeStr);
    get(Side::Right, EncoderPort::c1).dumpFile_.open(dirBase + "/rightC1" + timeStr);
    get(Side::Right, EncoderPort::c2).dumpFile_.open(dirBase + "/rightC2" + timeStr);
}

void EncoderService::start()
{
    initDumpFiles();

    using namespace std::placeholders;
    leftEncoder_.init(epollReactor_,
                      std::bind(&EncoderService::onEncoderTick, this, std::ref(get(Side::Left, EncoderPort::c1)), _1),
                      std::bind(&EncoderService::onEncoderTick, this, std::ref(get(Side::Left, EncoderPort::c2)), _1));
    leftEncoder_.init(epollReactor_,
                      std::bind(&EncoderService::onEncoderTick, this, std::ref(get(Side::Right, EncoderPort::c1)), _1),
                      std::bind(&EncoderService::onEncoderTick, this, std::ref(get(Side::Right, EncoderPort::c2)), _1));
}

void EncoderService::onEncoderTick(EncoderContext& ec, int level)
{
    auto timestamp = std::chrono::steady_clock::now();
    auto elapsedTime = timestamp - measurementBegin_;
    ec.measurements_.push_back({elapsedTime, level});
    ec.dumpFile_ << elapsedTime.count() << " " << level << std::endl;
}

EncoderContext &EncoderService::get(Side s, EncoderPort ep)
{
    if (s == Side::Left && ep == EncoderPort::c1)
    {
        return encoderContext_[0];
    }
    if (s == Side::Left && ep == EncoderPort::c2)
    {
        return encoderContext_[1];
    }
    if (s == Side::Right && ep == EncoderPort::c1)
    {
        return encoderContext_[2];
    }
    return encoderContext_[3];
}




}  // services
