#pragma once

#include "IPipelineEntity.hpp"
#include "SingleInputConsumer.hpp"
#include <array>
#include "opencv2/opencv.hpp"
#include <Networking/MessageSender.hpp>
#include <Common/ImageTypes.hpp>

namespace image_processing
{

class PicturePublisher : public SingleInputConsumer_1<cv::Mat>
{
public:
    explicit PicturePublisher(networking::MessageSender& messageSender,
                              CameraSide cammeraSide);
    void init() override;
private:
    void execute(cv::Mat& image) override;

    networking::MessageSender& messageSender_;
    CameraSide cammeraSide_;
};

}  // namespace image_processing
