#include "CameraDriver.hpp"
#include "opencv2/videoio.hpp"

#include <AppConfig.hpp>

namespace drivers
{
CameraDriver::CameraDriver(int cameraIndex)
    : cameraIndex_(cameraIndex)
    , isInitialized_(false)
{

}

CameraDriver::~CameraDriver()
{
    if (isInitialized_)
    {
        cap_.release();
    }
}

void CameraDriver::init()
{
    isInitialized_ = true;
    cap_.open(cameraIndex_);
    cap_.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    cap_.set(cv::CAP_PROP_FRAME_WIDTH, AppConfig::getInstance().getCameraWidth());
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT, AppConfig::getInstance().getCameraHeight());
}

void CameraDriver::getFrame(cv::Mat &imageOut)
{
    cap_ >> imageOut;
}

} // drivers
