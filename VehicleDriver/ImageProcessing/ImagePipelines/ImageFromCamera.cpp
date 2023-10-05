#include "ImageFromCamera.hpp"

namespace image_processing
{

ImageFromCamera::ImageFromCamera(drivers::CameraDriver &&cameraDriver)
        : cameraDriver_(std::move(cameraDriver))
{
}

void ImageFromCamera::init()
{
    cameraDriver_.init();
}

void ImageFromCamera::execute()
{
    cameraDriver_.getFrame(image_);
}

std::any ImageFromCamera::get(int outputPort)
{
    return std::any(&image_);
}

}  // namespace image_processing
