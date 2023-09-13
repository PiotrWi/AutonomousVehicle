#pragma once

#include <memory>

#include "Component.hpp"

namespace components
{

class CameraProcessingComponent : public Component
{
public:
    void start();
};

std::unique_ptr<Component> createCameraProcessingComponent();

}  // namespace components
