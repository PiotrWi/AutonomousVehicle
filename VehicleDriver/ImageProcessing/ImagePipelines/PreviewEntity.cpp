#include "PreviewEntity.hpp"

namespace image_processing
{

PreviewEntity::PreviewEntity(std::string windowName)
    : windowName_(std::move(windowName))
{
}

void PreviewEntity::init()
{
    cv::namedWindow(windowName_, cv::WINDOW_AUTOSIZE);
}

void PreviewEntity::execute(cv::Mat &image)
{
    if (not image.empty())
    {
        cv::imshow(windowName_, image);
        cv::waitKey(1);  // Gui will not appear without this... :]
    }
}



}  // namespace image_processing
