#include "PipelineFactory.hpp"

#include <string>

#include "ImagePipelines/ImageFromCamera.hpp"
#include "ImagePipelines/PreviewEntity.hpp"
#include "ImagePipelines/PicturePublisher.hpp"
#include "ImagePipelines/FlipImage.hpp"
#include <Drivers/CameraDriver.hpp>

namespace image_processing
{

using namespace std;

std::unique_ptr<Pipeline> createSingleCameraPreview()
{
    auto pipeline = std::make_unique<Pipeline>();

    drivers::CameraDriver leftCamera(0);
    pipeline->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipeline->add(new PreviewEntity("Preview"), "preview"s, {{0, "leftCameraIn", 0}});

    return pipeline;
}

std::unique_ptr<Pipeline> createDualCameraPreview()
{
    auto pipeline = std::make_unique<Pipeline>();

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipeline->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipeline->add(new ImageFromCamera(std::move(rightCamera)), "rightCameraIn"s);
    pipeline->add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}});
    pipeline->add(new FlipImage(), "flippedImageRight"s, {{0, "rightCameraIn", 0}});
    pipeline->add(new PreviewEntity("PreviewLeft"), "previewLeft"s, {{0, "flippedImageLeft", 0}});
    pipeline->add(new PreviewEntity("PreviewRight"), "previewRight"s, {{0, "flippedImageRight", 0}});

    return pipeline;
}

std::unique_ptr<Pipeline> createSingleCameraPublish(networking::MessageSender& messageSender)
{
    auto pipeline = std::make_unique<Pipeline>();

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipeline->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipeline->add(new ImageFromCamera(std::move(rightCamera)), "rightCameraIn"s);
    pipeline->add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}});
    pipeline->add(new FlipImage(), "flippedImageRight"s, {{0, "rightCameraIn", 0}});
    pipeline->add(new PicturePublisher(messageSender, CameraSide::LEFT ), "previewLeft"s, {{0, "flippedImageLeft", 0}});
    pipeline->add(new PicturePublisher(messageSender, CameraSide::RIGHT ), "previewRight"s, {{0, "flippedImageRight", 0}});

    return pipeline;
}

}  // namespace image_processing
