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
    auto areaOfIntrest = std::vector<cv::Point>{
        cv::Point{20, 539}, cv::Point {479, 260}, cv::Point {939, 539 }
    };

    auto outFrame = in | ToBinary{} | GaussianBlur {cv::Size(5, 5), 0.0} | Canny{150, 150} | FilterByMask{areaOfIntrest} ;
    out = in + calculateHoughLines(outFrame);
    return out;
}

}  // namespace road_lane_detection
}  // namespace image_processing