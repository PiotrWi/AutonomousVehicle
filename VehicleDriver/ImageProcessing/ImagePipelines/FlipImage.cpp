#include "FlipImage.hpp"

namespace image_processing
{
void FlipImage::execute(cv::Mat &arg)
{
    std::cout << "Going to flip" << std::endl;
    image_ = &arg;
    cv::flip(*image_, *image_, -1);
}

std::any FlipImage::get(int outputPort)
{
    return std::any(image_);
}

} // image_processing