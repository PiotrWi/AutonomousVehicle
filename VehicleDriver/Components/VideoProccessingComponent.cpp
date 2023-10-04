#include "VideoProccessingComponent.hpp"

#include <iostream>

#include "opencv2/highgui.hpp"

#include "VehicleDriver/ImageProcessing/ImageOperations/RoadLineDetection.hpp"

namespace
{
// TODO: Temporary. It shall be invested to some proper gui.

auto openVideo(const std::string& location)
{
    cv::VideoCapture cap;
    cap.open(location);
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

        auto frameWithLines = image_processing::road_lane_detection::applyLinesToImage(frame);

        cv::imshow("VideoProcessing",frameWithLines);
        if (cv::waitKey(33) >= 0) break;
    }
}

}  // namespace

namespace components
{

std::unique_ptr<Component> createVideoProcessingComponent(const std::string &input)
{
    return std::make_unique<VideoProcessingComponent>(input);
}

VideoProcessingComponent::VideoProcessingComponent(const std::string &input)
        : input_(input)
{
}

void VideoProcessingComponent::start()
{
    auto inputVideo = openVideo(input_);
    showMovie(inputVideo);
}

}  // namespace components
