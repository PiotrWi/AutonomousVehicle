#include "PipelineFactory.hpp"

#include <string>

#include <AppConfig.hpp>
#include "ImagePipelines/ImageFromCamera.hpp"
#include "ImagePipelines/PreviewEntity.hpp"
#include "ImagePipelines/PicturePublisher.hpp"
#include "ImagePipelines/FlipImage.hpp"
#include "ImagePipelines/DumpImage.hpp"
#include "ImagePipelines/CorrectImage.hpp"
#include <Drivers/CameraDriver.hpp>

namespace image_processing
{

using namespace std;

std::vector<std::unique_ptr<Pipeline>> createSingleCameraPreview()
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;
    pipelines.emplace_back(std::make_unique<Pipeline>());

    drivers::CameraDriver leftCamera(0);
    pipelines.back()->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipelines.back()->add(new PreviewEntity("Preview"), "preview"s, {{0, "leftCameraIn", 0}});

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createDualCameraPreview()
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;
    pipelines.emplace_back(std::make_unique<Pipeline>());

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.back()->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipelines.back()->add(new ImageFromCamera(std::move(rightCamera)), "rightCameraIn"s);
    pipelines.back()->add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}});
    pipelines.back()->add(new FlipImage(), "flippedImageRight"s, {{0, "rightCameraIn", 0}});
    pipelines.back()->add(new PreviewEntity("PreviewLeft"), "previewLeft"s, {{0, "flippedImageLeft", 0}});
    pipelines.back()->add(new PreviewEntity("PreviewRight"), "previewRight"s, {{0, "flippedImageRight", 0}});

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createDualCameraPublish(networking::MessageSender& messageSender)
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;
    pipelines.emplace_back(std::make_unique<Pipeline>());

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.back()->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipelines.back()->add(new ImageFromCamera(std::move(rightCamera)), "rightCameraIn"s);
    pipelines.back()->add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}});
    pipelines.back()->add(new FlipImage(), "flippedImageRight"s, {{0, "rightCameraIn", 0}});
    pipelines.back()->add(new PicturePublisher(messageSender, CameraSide::LEFT ), "publishLeft"s, {{0, "flippedImageLeft", 0}});
    pipelines.back()->add(new PicturePublisher(messageSender, CameraSide::RIGHT ), "publishRight"s, {{0, "flippedImageRight", 0}});

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createSingleCameraPublish(networking::MessageSender& messageSender)
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.emplace_back(std::make_unique<Pipeline>());
    pipelines.back()->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipelines.back()->add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}});
    pipelines.back()->add(new PicturePublisher(messageSender, CameraSide::LEFT ), "publishLeft"s, {{0, "flippedImageLeft", 0}});
    pipelines.back()->add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "left"), "dumpLeft"s, {{0, "flippedImageLeft", 0}});

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createParallelDualCameraPublish(networking::MessageSender& messageSender)
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.emplace_back(std::make_unique<Pipeline>());
    pipelines.back()->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipelines.back()->add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}});
    pipelines.back()->add(new PicturePublisher(messageSender, CameraSide::LEFT ), "publishLeft"s, {{0, "flippedImageLeft", 0}});
    pipelines.back()->add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "left"), "dumpLeft"s, {{0, "flippedImageLeft", 0}});

    pipelines.emplace_back(std::make_unique<Pipeline>());
    pipelines.back()->add(new ImageFromCamera(std::move(rightCamera)), "rightCameraIn"s);
    pipelines.back()->add(new FlipImage(), "flippedImageRight"s, {{0, "rightCameraIn", 0}});
    pipelines.back()->add(new PicturePublisher(messageSender, CameraSide::RIGHT ), "publishRight"s, {{0, "flippedImageRight", 0}});
    pipelines.back()->add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "right"), "dumpRight"s, {{0, "flippedImageRight", 0}});

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createParallelCorrectedDualCameraPublish(networking::MessageSender& messageSender)
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.emplace_back(std::make_unique<Pipeline>());
    pipelines.back()->add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s);
    pipelines.back()->add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}});
    pipelines.back()->add(new CorrectImage(AppConfig::getInstance().getLeftCoefficientFileLoc()), "correctedImageLeft", {{0, "flippedImageLeft"s, 0}});
    pipelines.back()->add(new PicturePublisher(messageSender, CameraSide::LEFT ), "publishLeft"s, {{0, "correctedImageLeft", 0}});
    pipelines.back()->add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "left"), "dumpLeft"s, {{0, "flippedImageLeft", 0}});

    pipelines.emplace_back(std::make_unique<Pipeline>());
    pipelines.back()->add(new ImageFromCamera(std::move(rightCamera)), "rightCameraIn"s);
    pipelines.back()->add(new FlipImage(), "flippedImageRight"s, {{0, "rightCameraIn", 0}});
    pipelines.back()->add(new CorrectImage(AppConfig::getInstance().getRightCoefficientFileLoc()), "correctedImageRight", {{0, "flippedImageRight"s, 0}});
    pipelines.back()->add(new PicturePublisher(messageSender, CameraSide::RIGHT ), "publishRight"s, {{0, "correctedImageRight", 0}});
    pipelines.back()->add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "right"), "dumpRight"s, {{0, "flippedImageRight", 0}});

    return pipelines;
}

}  // namespace image_processing
