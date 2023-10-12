#include "PipelineFactory.hpp"

#include <string>

#include <AppConfig.hpp>
#include "ImagePipelines/ImageFromCamera.hpp"
#include "ImagePipelines/PreviewEntity.hpp"
#include "ImagePipelines/PicturePublisher.hpp"
#include "ImagePipelines/FlipImage.hpp"
#include "ImagePipelines/DumpImage.hpp"
#include "ImagePipelines/ApplyCalibration.hpp"
#include <Drivers/CameraDriver.hpp>

namespace image_processing
{

using namespace std;

std::vector<std::unique_ptr<Pipeline>> createSingleCameraPreview()
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);

    pipelines.emplace_back(
            PipeLineBuilder()
                .add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s)
                .add(new PreviewEntity("Preview"), "preview"s, DefaultMapping{})
                .build());
    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createDualCameraPreview()
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.emplace_back(
            PipeLineBuilder()
                .add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s)
                .add(new ImageFromCamera(std::move(rightCamera)), "rightCameraIn"s)
                .add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}})
                .add(new FlipImage(), "flippedImageRight"s, {{0, "rightCameraIn", 0}})
                .add(new ApplyCalibration(AppConfig::getInstance().getLeftCoefficientFileLoc()), "correctedImageLeft", {{0, "flippedImageLeft"s, 0}})
                .add(new ApplyCalibration(AppConfig::getInstance().getRightCoefficientFileLoc()), "correctedImageRight", {{0, "flippedImageRight"s, 0}})
                .add(new PreviewEntity("PreviewLeft"), "previewLeft"s, {{0, "correctedImageLeft", 0}})
                .add(new PreviewEntity("PreviewRight"), "previewRight"s, {{0, "correctedImageRight", 0}})
                .build());

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createDualCameraPublish(networking::MessageSender& messageSender)
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.emplace_back(
            PipeLineBuilder()
                .add(new ImageFromCamera(std::move(leftCamera)), "leftCameraIn"s)
                .add(new ImageFromCamera(std::move(rightCamera)), "rightCameraIn"s)
                .add(new FlipImage(), "flippedImageLeft"s, {{0, "leftCameraIn", 0}})
                .add(new FlipImage(), "flippedImageRight"s, {{0, "rightCameraIn", 0}})
                .add(new PicturePublisher(messageSender, CameraSide::LEFT ), "publishLeft"s, {{0, "flippedImageLeft", 0}})
                .add(new PicturePublisher(messageSender, CameraSide::RIGHT ), "publishRight"s, {{0, "flippedImageRight", 0}})
                .build());

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createSingleCameraPublish(networking::MessageSender& messageSender)
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);

    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("left"s)
                .add(new ImageFromCamera(std::move(leftCamera)))
                .add(new FlipImage(), DefaultMapping{})
                .add(new PicturePublisher(messageSender, CameraSide::LEFT ), DefaultMapping{})
                .add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "left"), DefaultMapping{})
                .build());

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createParallelDualCameraPublish(networking::MessageSender& messageSender)
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("left"s)
                .add(new ImageFromCamera(std::move(leftCamera)))
                .add(new FlipImage(), DefaultMapping{})
                .add(new PicturePublisher(messageSender, CameraSide::LEFT ), DefaultMapping{})
                .add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "left"), DefaultMapping{})
                .build());

    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("right"s)
                .add(new ImageFromCamera(std::move(rightCamera)))
                .add(new FlipImage(), DefaultMapping{})
                .add(new PicturePublisher(messageSender, CameraSide::RIGHT ), DefaultMapping{})
                .add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "right"), DefaultMapping{})
                .build());

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createParallelCorrectedDualCameraPublish(networking::MessageSender& messageSender)
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(0);
    drivers::CameraDriver rightCamera(2);

    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("left"s)
                    .add(new ImageFromCamera(std::move(leftCamera)))
                    .add(new FlipImage(), DefaultMapping{})
                    .add(new ApplyCalibration(AppConfig::getInstance().getLeftCoefficientFileLoc()), DefaultMapping{})
                    .add(new PicturePublisher(messageSender, CameraSide::LEFT ),  DefaultMapping{})
                    .add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "left"), DefaultMapping{})
                    .build());

    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("right"s)
                    .add(new ImageFromCamera(std::move(rightCamera)))
                    .add(new FlipImage(), DefaultMapping{})
                    .add(new ApplyCalibration(AppConfig::getInstance().getRightCoefficientFileLoc()), DefaultMapping{})
                    .add(new PicturePublisher(messageSender, CameraSide::RIGHT ), DefaultMapping{})
                    .add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "right"), DefaultMapping{})
                    .build());

    return pipelines;
}

}  // namespace image_processing
