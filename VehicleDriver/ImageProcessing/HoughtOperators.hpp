#pragma once

#include <vector>
#include "opencv2/opencv.hpp"

namespace image_processing
{

struct RoThetaLinesPlusColor
{
    std::vector<cv::Vec2f> lines;
    cv::Scalar color = cv::Scalar(0,0,255);
};

struct DoublePointLinesPlusColor
{
    std::vector<cv::Vec4i> lines;
    cv::Scalar color = cv::Scalar(0,0,255);
};

cv::Mat operator+ (const cv::Mat& in, const DoublePointLinesPlusColor& params);
cv::Mat operator+ (const cv::Mat& in, const RoThetaLinesPlusColor& params);

RoThetaLinesPlusColor calculateHoughLines(const cv::Mat& in);
DoublePointLinesPlusColor calculateHoughPLines(const cv::Mat& in);

}  // namespace image_processing
