#include "PreviewEntity.hpp"

namespace image_processing
{

PreviewEntity::PreviewEntity(std::string windowName)
    : windowName_(windowName)
{
}

void PreviewEntity::init()
{
    cv::namedWindow(windowName_.c_str(), cv::WINDOW_AUTOSIZE);
}

void PreviewEntity::execute(cv::Mat &image)
{
    if (not image.empty())
    {
        cv::imshow(windowName_.c_str(), image);
        cv::waitKey(1);  // Gui will not appear without this... :]
    }
}



}  // namespace image_processing
