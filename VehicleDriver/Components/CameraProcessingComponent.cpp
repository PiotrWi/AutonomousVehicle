#include "CameraProcessingComponent.hpp"

#include "opencv2/opencv.hpp"

namespace
{
// TODO: Temporary. It shall be invested to some proper gui.

auto openVideo()
{
    cv::VideoCapture cap;
    cap.open(0);
    return cap;
}

auto showMovie(cv::VideoCapture& cap)
{
    cv::namedWindow("VideoProcessing", cv::WINDOW_AUTOSIZE);
    cv::Mat frame;

    for (;;)
    {
        cap >> frame;
        if (frame.empty()) break;
        cv::imshow("VideoProcessing",frame);
        if (cv::waitKey(33) >= 0) break;
    }
}

}  // namespace

namespace components
{

std::unique_ptr<Component> createCameraProcessingComponent()
{
    return std::make_unique<CameraProcessingComponent>();
}

void CameraProcessingComponent::start()
{
    auto cam = openVideo();
    showMovie(cam);
}

}  // namespace components
