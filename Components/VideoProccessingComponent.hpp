#pragma once

#include <memory>
#include "Component.hpp"

class VideoProcessingComponent : public Component
{
public:
    VideoProcessingComponent(const std::string& input);
    void start();
private:
    std::string input_;
};

std::unique_ptr<VideoProcessingComponent> createVideoProcessingComponent(const std::string& input);
