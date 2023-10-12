#pragma once

#include <memory>
#include <mutex>
#include <condition_variable>
#include "Component.hpp"
#include <ImageProcessing/Pipeline.hpp>

namespace components
{

class CameraProcessingComponent : public Component
{
public:
    explicit CameraProcessingComponent(std::vector<std::unique_ptr<image_processing::Pipeline>>&& pipelines);
    void start() override;
    void stop() override;
private:
    void run(image_processing::Pipeline&);

    std::condition_variable notifyFramesToExecute_;
    std::mutex framesToExecuteMutex_;
    int framesToExecute = 0;

    std::atomic<bool> stopped_ = false;
    std::vector<std::unique_ptr<image_processing::Pipeline>> pipelines_;
};

std::unique_ptr<Component> createCameraProcessingComponent(std::vector<std::unique_ptr<image_processing::Pipeline>>&& pipelines);

}  // namespace components
