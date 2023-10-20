#pragma once

#include <string>
#include <opencv2/opencv.hpp>

#include <Common/ImageTypes.hpp>
#include <CurrentRequestedSpeed.pb.h>
#include <PublishImage.pb.h>

CurrentRequestedSpeed createCurrentRequestedSpeed(int leftWheel, int rightWheel);
PublishImage createPublishImage(CameraSide cameraSide, cv::Mat& image);
