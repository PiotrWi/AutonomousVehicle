#pragma once

#include "IPipelineEntity.hpp"

#include <string>

#include <opencv2/opencv.hpp>

namespace image_processing
{

class ImageFromFile : public IProducerPipelineEntity
{
public:
    explicit ImageFromFile(std::string filename);
    void init() override;
    void execute() override;
    std::string getDefaultName() const override;
    std::any get(int outputPort) override;
private:
    std::string filename_;
    cv::Mat image_;
};

}  // namespace image_processing
