#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <opencv2/opencv.hpp>

namespace image_processing
{

using TCameraMatrix = cv::Mat;
using TDistortionMatrix = cv::Mat;
using TImageSize = cv::Size;
using TFound = bool;
using TImageCalibrationPoints = std::vector<cv::Point2f>;

std::tuple<TCameraMatrix, TDistortionMatrix, TImageSize> readCoeffsFromFile(const std::string& dumpFileLocation);

TImageCalibrationPoints addCornersByHand(cv::Mat image, cv::Size cornersExpectedSize);
std::tuple<TFound, TImageCalibrationPoints> findChessBoardCornersByOpenCv(cv::Mat mat, cv::Size2i size);

void printCorners(std::string windowName, cv::Mat image, cv::Size size, const TImageCalibrationPoints& points);

// sandbox functions:
[[maybe_unused]]  // does not work
std::tuple<TFound, TImageCalibrationPoints> findCornersByKMeans(cv::Mat mat, cv::Size2i size);
[[maybe_unused]]  // does not work
std::tuple<TFound, TImageCalibrationPoints> findCornerOnTransformedImage(cv::Mat image, cv::Size cornersSize);

}  // namespace image_processing
