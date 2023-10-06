#pragma once

#include <memory>
#include "Component.hpp"

namespace components
{

class VideoProcessingComponent : public Component
{
public:
    explicit VideoProcessingComponent(const std::string& input);
    void start() override;
    void stop() override;
private:
    std::string input_;
};

std::unique_ptr<Component> createVideoProcessingComponent(const std::string& input);

}  // namespace components
