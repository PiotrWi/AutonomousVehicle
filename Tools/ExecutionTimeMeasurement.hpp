#pragma once

#include <chrono>
#include <iostream>

struct RaiiExecutionTimeMeasurement
{
    RaiiExecutionTimeMeasurement(const char* prefix)
            : prefix_(prefix)
    {
        begin_ = std::chrono::system_clock::now();
    }
    ~RaiiExecutionTimeMeasurement()
    {
        auto end = std::chrono::system_clock::now();
        auto elapsed = end - begin_;
        std::cout << prefix_ << " time needed: " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << "ms" << std::endl;
    }
private:
    const char* prefix_;
    std::chrono::system_clock::time_point begin_;
};