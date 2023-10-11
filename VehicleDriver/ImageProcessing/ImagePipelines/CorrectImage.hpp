#pragma once

#include <opencv2/opencv.hpp>

#include "SingleInputConsumer.hpp"

namespace image_processing
{

class CorrectImage : public SingleInputConsumer_1<cv::Mat>, public IProducerPipelineEntity
{
public:
    explicit CorrectImage(const std::string& coefficientFile);
    void init() override;
    std::any get(int outputPort) override;
private:
    void execute(cv::Mat&) override;

    const std::string &coefficientFile_;
    cv::Mat map1;
    cv::Mat map2;
    cv::Mat* adjustedImage_;
};

} // image_processing
