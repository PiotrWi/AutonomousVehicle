#include "CameraProcessingComponent.hpp"

#include <iostream>
#include <thread>
#include <Tools/CreateTimmer.hpp>
#include <Tools/ExecutionTimeMeasurement.hpp>

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

    tools::createRepeatingTimer(1000000/10, [this](){
        std::lock_guard<std::mutex> lock(framesToExecuteMutex_);
        framesToExecute += pipelines_.size();
        for (int i = 0; i < pipelines_.size(); ++i)
        {
            notifyFramesToExecute_.notify_one();
        }
    });
}

void CameraProcessingComponent::run(image_processing::Pipeline& pipeline)
{
    while (true)
    {
        {
            std::unique_lock lk(framesToExecuteMutex_);
            notifyFramesToExecute_.wait(lk, [this](){ return framesToExecute; });
            framesToExecute -= 1;
        }
        pipeline.execute();
    }
}


}  // namespace components
