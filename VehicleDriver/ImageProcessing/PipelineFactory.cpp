#include "PipelineFactory.hpp"

#include <string>

#include <AppConfig.hpp>
#include "ImagePipelines/ImageFromCamera.hpp"
#include "ImagePipelines/ImageFromFile.hpp"
#include "ImagePipelines/PreviewEntity.hpp"
#include "ImagePipelines/PicturePublisher.hpp"
#include "ImagePipelines/FlipImage.hpp"
#include "ImagePipelines/DumpImage.hpp"
#include "ImagePipelines/ApplyCalibration.hpp"
#include <Drivers/CameraDriver.hpp>

namespace image_processing
{

using namespace std;

std::vector<std::unique_ptr<Pipeline>> createSingleCorrectedImage()
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(2);
    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("left"s)
                    .add(new ImageFromFile("/home/pioter/calibData/Right_112"))
                    .add(new ApplyCalibration(AppConfig::getInstance().getLeftCoefficientFileLoc()), DefaultMapping{})
                    .build());
    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createDualCameraPreview()
{
    std::vector<std::unique_ptr<Pipeline>> pipelines;

    drivers::CameraDriver leftCamera(2);
    drivers::CameraDriver rightCamera(0);

    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("left"s)
                    .add(new ImageFromCamera(std::move(leftCamera)))
                    .add(new FlipImage(), DefaultMapping{})
                    .add(new ApplyCalibration(AppConfig::getInstance().getLeftCoefficientFileLoc()), DefaultMapping{})
                    .add(new PreviewEntity("PreviewLeft"),DefaultMapping{})
                    .build());

    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("right"s)
                    .add(new ImageFromCamera(std::move(rightCamera)))
                    .add(new FlipImage(), DefaultMapping{})
                    .add(new ApplyCalibration(AppConfig::getInstance().getRightCoefficientFileLoc()), DefaultMapping{})
                    .add(new PreviewEntity("PreviewRight"),DefaultMapping{})
                    .build());

    return pipelines;
}

std::vector<std::unique_ptr<Pipeline>> createParallelCorrectedDualCameraPublish(networking::MessageSender<networking::AccessPoint>& messageSender)
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
                    .add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "left"), {{0, "leftApplyCalibration", 0}})
                    .build());

    pipelines.emplace_back(
            PipeLineBuilderWithPrefix("right"s)
                    .add(new ImageFromCamera(std::move(rightCamera)))
                    .add(new FlipImage(), DefaultMapping{})
                    .add(new ApplyCalibration(AppConfig::getInstance().getRightCoefficientFileLoc()), DefaultMapping{})
                    .add(new PicturePublisher(messageSender, CameraSide::RIGHT ), DefaultMapping{})
                    .add(new DumpImage(AppConfig::getInstance().getCameraDumpDirectory(), "right"), {{0, "rightApplyCalibration", 0}})
                    .build());

    return pipelines;
}

}  // namespace image_processing
