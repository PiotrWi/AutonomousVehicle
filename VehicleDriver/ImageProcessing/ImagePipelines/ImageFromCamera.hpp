#pragma once

#include "IPipelineEntity.hpp"
#include <Drivers/CameraDriver.hpp>

namespace image_processing
{

class ImageFromCamera
    : public IProducerPipelineEntity
{
public:
    explicit ImageFromCamera(drivers::CameraDriver &&cameraDriver);
    void init() override;
    void execute() override;
    std::any get(int outputPort) override;
private:
    drivers::CameraDriver cameraDriver_;
    cv::Mat image_;
};

} // namespace image_processing