#pragma once

#include <memory>
#include <string>

#include "Component.hpp"

namespace components
{

class CalibrationComponent : public Component
{
public:
    explicit CalibrationComponent(std::string&& calibrationFilesDirectory);
    void start() override;
    void stop() override;
private:
    std::string calibrationFilesDirectory_;
};

std::unique_ptr<Component> createCalibrationComponent(std::string&& calibrationFilesDirectory);

} // components
