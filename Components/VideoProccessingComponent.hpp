#pragma once

#include <memory>
#include "Component.hpp"

namespace components
{

class VideoProcessingComponent : public Component
{
public:
    VideoProcessingComponent(const std::string& input);
    void start() override;
private:
    std::string input_;
};

std::unique_ptr<Component> createVideoProcessingComponent(const std::string& input);

}  // namespace components