#pragma once

#include <memory>

#include "Component.hpp"
#include <ImageProcessing/Pipeline.hpp>

namespace components
{
/*
 * Sandbox component to prototype new implementations
 */
class PrototypeComponent : public Component
{
public:
    explicit PrototypeComponent(std::vector<std::unique_ptr<image_processing::Pipeline>>&& pipelines);
    virtual void start() override;
    virtual void stop() override;
private:
    std::vector<std::unique_ptr<image_processing::Pipeline>> pipelines_;
};

std::unique_ptr<Component> createPrototypeComponent(std::vector<std::unique_ptr<image_processing::Pipeline>>&& pipelines);

} // components
