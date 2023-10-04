#include "CameraProcessingComponent.hpp"

#include <iostream>
#include <thread>
#include <Tools/CreateTimmer.hpp>
#include <Tools/ExecutionTimeMeasurement.hpp>

namespace components
{

CameraProcessingComponent::CameraProcessingComponent(std::unique_ptr<image_processing::Pipeline>&& pipeline)
    : pipeline_(std::move(pipeline))
{
}

std::unique_ptr<Component> createCameraProcessingComponent(std::unique_ptr<image_processing::Pipeline>&& pipeline)
{
    return std::make_unique<CameraProcessingComponent>(std::move(pipeline));
}

void CameraProcessingComponent::start()
{
    std::thread t([this](){ run(); });
    t.detach();
}

void CameraProcessingComponent::run()
{
    std::cout << "[CameraProcessingComponent] run" << std::endl;
    pipeline_->init();
    tools::createRepeatingTimer(1000000/10, [this](){
        std::lock_guard<std::mutex> lock(shallReadFrameMutex);
        shallReadFrame = true;
        notifyFrameTime_.notify_one();
    });

    while (true)
    {
        {
            std::unique_lock lk(shallReadFrameMutex);
            notifyFrameTime_.wait(lk, [this](){ return shallReadFrame; });
            shallReadFrame = false;
        }
        RaiiExecutionTimeMeasurement timeMeasurement("single camera frame");
        pipeline_->execute();
    }
}


}  // namespace components
