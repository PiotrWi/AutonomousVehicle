#pragma once

#include <chrono>
#include <iostream>

struct RaiiExecutionTimeMeasurement
{
    explicit RaiiExecutionTimeMeasurement(const char* prefix)
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

struct RaiiMultipleStepExecutionTimeMeasurement
{
public:
    explicit RaiiMultipleStepExecutionTimeMeasurement(const char* prefix)
            : prefix_(prefix)
    {
        begin_ = std::chrono::system_clock::now();
    }
    void step(const char* label)
    {
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_);
        steps_.emplace_back(std::make_pair(label, elapsed));
    }
    ~RaiiMultipleStepExecutionTimeMeasurement()
    {
        std::cout << prefix_;
        for (auto&& step : steps_)
        {
            std::cout << step.first << " " << step.second.count() << "ms ";
        }
        std::cout << std::endl;
    }
private:
    const char* prefix_;
    std::vector<std::pair<const char*, std::chrono::milliseconds>> steps_;
    std::chrono::system_clock::time_point begin_;
};