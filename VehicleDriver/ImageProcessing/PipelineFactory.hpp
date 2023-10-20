#pragma once

#include <memory>
#include "Pipeline.hpp"

#include <CommunicationProtocol/networking/MessageSender.hpp>
#include "CommunicationProtocol/networking/AccessPoint.hpp"

namespace image_processing
{

std::vector<std::unique_ptr<Pipeline>> createDualCameraPreview();
std::vector<std::unique_ptr<Pipeline>> createSingleCorrectedImage();
std::vector<std::unique_ptr<Pipeline>> createParallelCorrectedDualCameraPublish(
        networking::MessageSender<networking::AccessPoint>& messageSender);

}  // namespace image_processing
