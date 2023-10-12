#pragma once

#include <memory>
#include "Pipeline.hpp"

#include <Networking/MessageSender.hpp>

namespace image_processing
{

std::vector<std::unique_ptr<Pipeline>> createDualCameraPreview();
std::vector<std::unique_ptr<Pipeline>> createSingleCorrectedImage();
std::vector<std::unique_ptr<Pipeline>> createParallelCorrectedDualCameraPublish(networking::MessageSender& messageSender);

}  // namespace image_processing
