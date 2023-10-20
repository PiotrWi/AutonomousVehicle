#include "CameraProcessingComponent.hpp"

#include <iostream>
#include <thread>

#include <AppConfig.hpp>
#include <Tools/CreateTimmer.hpp>

namespace components
{

CameraProcessingComponent::CameraProcessingComponent(std::vector<std::unique_ptr<image_processing::Pipeline>>&& pipelines)
    : pipelines_(std::move(pipelines))
{
}

std::unique_ptr<Component> createCameraProcessingComponent(std::vector<std::unique_ptr<image_processing::Pipeline>>&& pipelines)
{
    return std::make_unique<CameraProcessingComponent>(std::move(pipelines));
}

void CameraProcessingComponent::start()
{
    std::cout << "[CameraProcessingComponent] start" << std::endl;
    for (auto& pipeline: pipelines_)
    {
        pipeline->init();
    }

    for (auto& pipeline: pipelines_)
    {
        std::thread t([&]() {run(*pipeline);} );
        t.detach();
    }

    auto cameraFps = AppConfig::getInstance().getCameraFps();
    tools::createRepeatingTimer(1000000/cameraFps, [this](){
        std::lock_guard<std::mutex> lock(framesToExecuteMutex_);
        framesToExecute += static_cast<int>(pipelines_.size());
        for (unsigned int i = 0; i < pipelines_.size(); ++i)
        {
            notifyFramesToExecute_.notify_one();
        }
    });
}

void CameraProcessingComponent::run(image_processing::Pipeline& pipeline)
{
    while (not stopped_.load())
    {
        {
            std::unique_lock lk(framesToExecuteMutex_);
            notifyFramesToExecute_.wait(lk, [this](){ return framesToExecute; });
            framesToExecute -= 1;
        }
        pipeline.execute();
    }
}

void CameraProcessingComponent::stop()
{
    stopped_ = true;
}


}  // namespace components
