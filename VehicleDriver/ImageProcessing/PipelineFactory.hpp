#pragma once

#include <memory>
#include "Pipeline.hpp"

#include <Networking/MessageSender.hpp>

namespace image_processing
{

std::vector<std::unique_ptr<Pipeline>> createSingleCameraPreview();
std::vector<std::unique_ptr<Pipeline>> createDualCameraPreview();
std::vector<std::unique_ptr<Pipeline>> createDualCameraPublish(networking::MessageSender& messageSender);
std::vector<std::unique_ptr<Pipeline>> createSingleCameraPublish(networking::MessageSender& messageSender);
std::vector<std::unique_ptr<Pipeline>> createParallelDualCameraPublish(networking::MessageSender& messageSender);
std::vector<std::unique_ptr<Pipeline>> createParallelCorrectedDualCameraPublish(networking::MessageSender& messageSender);

}  // namespace image_processing
