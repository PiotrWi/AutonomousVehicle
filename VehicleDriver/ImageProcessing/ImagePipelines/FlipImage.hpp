#pragma  once

#include <opencv2/opencv.hpp>
#include "IPipelineEntity.hpp"
#include "SingleInputConsumer.hpp"

namespace image_processing
{

class FlipImage : public SingleInputConsumer_1<cv::Mat>, public IProducerPipelineEntity
{
public:
    void init() override {}
    void execute(cv::Mat& arg)  override;
    std::any get(int outputPort) override;
    virtual std::string getDefaultName() const override;
private:
    cv::Mat* image_;
};

} // image_processing
