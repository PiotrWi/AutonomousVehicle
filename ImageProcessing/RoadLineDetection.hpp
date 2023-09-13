#pragma once

#include "opencv2/opencv.hpp"

namespace image_processing
{
namespace road_lane_detection
{

cv::Mat applyLinesToImage(const cv::Mat& in);

}  // namespace road_lane_detection
}  // namespace image_processing