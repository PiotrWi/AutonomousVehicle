#include "HoughtOperators.hpp"

namespace image_processing
{

cv::Mat operator+(const cv::Mat &in, const DoublePointLinesPlusColor &params)
{
    const cv::Mat out = in;

    const auto &lines = params.lines;
    const auto &color = params.color;

    for (size_t i = 0; i < lines.size(); i++) {
        line(out, cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3]), color, 3, cv::LINE_AA);
    }
    return out;
}

cv::Mat operator+(const cv::Mat &in, const RoThetaLinesPlusColor &params)
{
    const cv::Mat out = in;

    const auto &lines = params.lines;
    const auto &color = params.color;

    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(out, pt1, pt2, color, 3, cv::LINE_AA);
    }
    return out;
}

RoThetaLinesPlusColor calculateHoughLines(const cv::Mat &in)
{
    RoThetaLinesPlusColor out;
    cv::HoughLines(in, out.lines, 3, 0.1, 100);
    return out;
}

DoublePointLinesPlusColor calculateHoughPLines(const cv::Mat &in)
{
    DoublePointLinesPlusColor out;
    cv::HoughLinesP(in, out.lines, 3, 0.1, 50, 20);
    return out;
}

}  // namespace image_processing
