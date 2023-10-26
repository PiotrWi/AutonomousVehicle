#pragma once

#include <chrono>
#include <fstream>
#include <vector>
#include <utility>

#include <VehicleDriver/Drivers/EncodersDriver.hpp>
#include <VehicleDriver/Drivers/EPoolReactor/EpollReactor.hpp>

enum class Side
{
    Left,
    Right,
};

enum class EncoderPort
{
    c1,
    c2,
};

using TMeasurementTimeStamp = std::decay_t<decltype(std::chrono::steady_clock::now())>;
using TDuration = std::decay_t<decltype(std::declval<TMeasurementTimeStamp>() - std::declval<TMeasurementTimeStamp>())>;
struct EncoderContext
{
    std::vector<std::pair<TDuration, int>> measurements_;
    std::ofstream dumpFile_;
};

namespace services
{

class EncoderService
{
public:
    explicit EncoderService(drivers::epoll_reactor::EpollReactor& epollReactor);
    void start();
private:
    void initDumpFiles();
    void onEncoderTick(EncoderContext&, int level);
    EncoderContext& get(Side, EncoderPort);

    drivers::epoll_reactor::EpollReactor& epollReactor_;
    drivers::EncoderDriver leftEncoder_;
    drivers::EncoderDriver rightEncoder_;

    const TMeasurementTimeStamp measurementBegin_ = std::chrono::steady_clock::now();
    EncoderContext encoderContext_[4];
};

} // drivers
