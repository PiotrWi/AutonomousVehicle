#pragma once

#include <opencv2/opencv.hpp>

#include "IPipelineEntity.hpp"
#include "SingleInputConsumer.hpp"

namespace image_processing
{

class DumpImage : public SingleInputConsumer_1<cv::Mat>
{
public:
    explicit DumpImage(const char* localization, const char* prefix);
    void init() override;
private:
    void execute(cv::Mat& image) override;
    const char *localization_;
    const char *prefix_;
    std::string dirrectory_;
};

} // image_processing
