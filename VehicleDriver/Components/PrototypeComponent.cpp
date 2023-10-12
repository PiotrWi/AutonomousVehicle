#include <opencv2/opencv.hpp>
#include "PrototypeComponent.hpp"

namespace components
{
std::unique_ptr<Component> createPrototypeComponent(std::vector<std::unique_ptr<image_processing::Pipeline>> &&pipelines)
{
    return std::make_unique<PrototypeComponent>(std::move(pipelines));
}

PrototypeComponent::PrototypeComponent(std::vector<std::unique_ptr<image_processing::Pipeline>> &&pipelines)
     : pipelines_(std::move(pipelines))
{
}

void PrototypeComponent::stop()
{
}

void PrototypeComponent::start()
{
    auto& pipeline = pipelines_.front();
    pipeline->init();
    pipeline->execute();
    auto image = *std::any_cast<cv::Mat*>(pipeline->getOut());
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

    cv::Size tableSize = {9, 6};

    std::vector<cv::Point2f> corners;
    auto found = cv::findChessboardCorners(image, tableSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
    if (not found)
    {
        std::cerr << "Pattern not found" << std::endl;
    }
}

} // components