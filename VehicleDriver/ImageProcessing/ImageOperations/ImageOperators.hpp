#pragma once

#include "opencv2/opencv.hpp"

namespace image_processing
{

class ToBinary
{
};

cv::Mat operator|(const cv::Mat &in, const ToBinary &)
{
    cv::Mat out;
    cv::cvtColor(in, out, cv::COLOR_BGR2GRAY);
    return out;
}

class AdaptiveThreshold
{
public:
    double maxValue;
    int method;
    int type;
    int blockSize;
    double delta;
};

class BinaryAdaptiveTreshold : public AdaptiveThreshold
{
public:
    BinaryAdaptiveTreshold(int blockSize, double c)
            : AdaptiveThreshold(255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, blockSize, c)
    {}
};

cv::Mat operator|(const cv::Mat &in, const AdaptiveThreshold &params)
{
    cv::Mat out;
    cv::adaptiveThreshold(in, out, params.maxValue, params.method, params.type, params.blockSize, params.delta);
    return out;
}

class Threshold
{
public:
    double thresh;
    double maxValue;
    int thresholdType;
};

class BinaryThreshold : public Threshold
{
public:
    explicit BinaryThreshold(double thresh) : Threshold(thresh, 255, cv::THRESH_BINARY)
    {}
};

cv::Mat operator|(const cv::Mat &in, const Threshold &params)
{
    cv::Mat out;
    cv::threshold(in, out, params.thresh, params.maxValue, params.thresholdType);
    return out;
}

class Sobel
{
public:
    int ddepth;
    int xorder;
    int yorder;
    int ksize;
};

cv::Mat operator|(const cv::Mat &in, const Sobel &params)
{
    cv::Mat out;
    cv::Sobel(in, out, params.ddepth, params.xorder, params.yorder, params.ksize);
    return out;
}

class GaussianBlur
{
public:
    cv::Size kSize;
    double sigmaX;
};

cv::Mat operator|(const cv::Mat &in, const GaussianBlur &params)
{
    cv::Mat out;
    cv::GaussianBlur(in, out, params.kSize, params.sigmaX);
    return out;
}

class Canny
{
public:
    double threshold1;
    double threshold2;
};

cv::Mat operator|(const cv::Mat &in, const Canny &params)
{
    cv::Mat out;
    cv::Canny(in, out, params.threshold1, params.threshold2);
    return out;
}

class FilterByMask
{
public:
    std::vector<cv::Point> points;
};

cv::Mat operator|(const cv::Mat& in, const FilterByMask &params)
{
    cv::Mat mask = cv::Mat::zeros(in.size(), CV_8U);
    cv::Mat out = in;

    cv::fillConvexPoly(mask, params.points.data(), params.points.size(), cv::Scalar(255));
    return cv::min(out, mask);
}

}  // namespace image_processing
