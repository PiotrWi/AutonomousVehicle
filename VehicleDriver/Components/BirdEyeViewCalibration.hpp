#pragma once

#include <memory>

#include "Component.hpp"
#include <ImageProcessing/Pipeline.hpp>

namespace components
{

class BirdEyeViewCalibration : public Component
{
public:
    explicit BirdEyeViewCalibration(std::vector<std::unique_ptr<image_processing::Pipeline>>&& pipelines);
    virtual void start() override;
    virtual void stop() override;
private:
    std::vector<std::unique_ptr<image_processing::Pipeline>> pipelines_;
};

std::unique_ptr<Component> createBirdEyeViewCalibration(std::vector<std::unique_ptr<image_processing::Pipeline>>&& pipelines);

} // components
