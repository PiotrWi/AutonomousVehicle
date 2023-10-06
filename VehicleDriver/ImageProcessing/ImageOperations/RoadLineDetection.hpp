#pragma once

#include "opencv2/opencv.hpp"

namespace image_processing::road_lane_detection
{

cv::Mat applyLinesToImage(const cv::Mat& in);

}  // namespace image_processing
