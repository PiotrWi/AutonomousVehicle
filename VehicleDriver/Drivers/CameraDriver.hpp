#pragma once

#include "opencv2/opencv.hpp"

namespace drivers
{

class CameraDriver
{
public:
    explicit CameraDriver(int cameraIndex);
    ~CameraDriver();
    void init();
    void getFrame(cv::Mat& imageOut);
private:
    cv::VideoCapture cap_;
    int cameraIndex_;
    bool isInitialized_;
};

} // drivers
