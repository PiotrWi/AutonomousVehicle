#pragma once

#include <opencv2/opencv.hpp>

#include "IPipelineEntity.hpp"
#include "SingleInputConsumer.hpp"

namespace image_processing
{

class DumpImage : public SingleInputConsumer_1<cv::Mat>
{
public:
    explicit DumpImage(std::string localization, const char* prefix);
    void init() override;
    virtual std::string getDefaultName() const override;
private:
    void execute(cv::Mat& image) override;
    std::string localization_;
    const char *prefix_;
    std::string dirrectory_;
};

} // image_processing
