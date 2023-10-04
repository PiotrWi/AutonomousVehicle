#pragma once

#include <memory>
#include "Pipeline.hpp"

#include <Networking/MessageSender.hpp>

namespace image_processing
{

std::unique_ptr<Pipeline> createSingleCameraPreview();
std::unique_ptr<Pipeline> createDualCameraPreview();
std::unique_ptr<Pipeline> createSingleCameraPublish(networking::MessageSender& messageSender);

}  // namespace image_processing
