#include "CameraDriver.hpp"

namespace drivers
{
CameraDriver::CameraDriver(int cameraIndex)
    : cameraIndex_(cameraIndex)
    , isInitialized_(false)
{

}

CameraDriver::~CameraDriver()
{
}

void CameraDriver::init()
{
    cap_.open(cameraIndex_);
    cap_.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
}

void CameraDriver::getFrame(cv::Mat &imageOut)
{
    cap_ >> imageOut;
}

} // drivers
