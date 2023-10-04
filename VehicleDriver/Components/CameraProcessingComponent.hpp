#pragma once

#include <memory>
#include <mutex>
#include <condition_variable>
#include "Component.hpp"
#include <Drivers/CameraDriver.hpp>
#include <ImageProcessing/Pipeline.hpp>

namespace components
{

class CameraProcessingComponent : public Component
{
public:
    explicit CameraProcessingComponent(std::unique_ptr<image_processing::Pipeline>&& pipeline);
    void start() override;
private:
    void run();

    std::condition_variable notifyFrameTime_;
    std::mutex shallReadFrameMutex;
    bool shallReadFrame = false;

    std::unique_ptr<image_processing::Pipeline> pipeline_;
};

std::unique_ptr<Component> createCameraProcessingComponent(std::unique_ptr<image_processing::Pipeline>&& pipeline);

}  // namespace components
