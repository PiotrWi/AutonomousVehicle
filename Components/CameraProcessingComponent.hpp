#pragma once

#include <memory>

#include "Component.hpp"

namespace components
{

class CameraProcessingComponent : public Component
{
public:
    void start() override;
};

std::unique_ptr<Component> createCameraProcessingComponent();

}  // namespace components
