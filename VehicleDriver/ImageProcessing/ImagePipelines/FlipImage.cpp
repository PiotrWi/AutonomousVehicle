#include "FlipImage.hpp"

namespace image_processing
{
void FlipImage::execute(cv::Mat &arg)
{
    image_ = &arg;
    cv::flip(*image_, *image_, -1);
}

std::any FlipImage::get(int outputPort)
{
    return {image_};
}

} // image_processing