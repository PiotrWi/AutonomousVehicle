#include "RoadLineDetection.hpp"
#include "ImageOperators.hpp"
#include "HoughtOperators.hpp"

namespace image_processing
{
namespace road_lane_detection
{

cv::Mat applyLinesToImage(const cv::Mat& in)
{
    auto out = in;
    auto outFrame = in | ToBinary{} | GaussianBlur {cv::Size(5, 5), 0.0} | Canny{150, 150};
    out = in + calculateHoughLines(outFrame);
    return out;
}

}  // namespace road_lane_detection
}  // namespace image_processing