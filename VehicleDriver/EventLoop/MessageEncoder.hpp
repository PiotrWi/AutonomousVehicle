#pragma once

#include <string>
#include <opencv2/opencv.hpp>

#include <Common/ImageTypes.hpp>

std::string createCurrentRequestedSpeed(int leftWheel, int rightWheel);
std::string createPublishImage(CameraSide cameraSide, cv::Mat& image);
