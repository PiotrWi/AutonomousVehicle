#pragma once

#include "IPipelineEntity.hpp"
#include "SingleInputConsumer.hpp"
#include "opencv2/opencv.hpp"

namespace image_processing
{

class PreviewEntity : public SingleInputConsumer_1<cv::Mat>
{
public:
    explicit PreviewEntity (std::string windowName);
    void init() override;
private:
    void execute(cv::Mat& image) override;
    std::string windowName_;
};

}  // namespace image_processing
