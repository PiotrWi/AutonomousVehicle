#pragma once

#include "IPipelineEntity.hpp"
#include "SingleInputConsumer.hpp"
#include <array>
#include "opencv2/opencv.hpp"
#include <CommunicationProtocol/networking/MessageSender.hpp>
#include "CommunicationProtocol/networking/AccessPoint.hpp"
#include <Common/ImageTypes.hpp>

namespace image_processing
{

class PicturePublisher : public SingleInputConsumer_1<cv::Mat>
{
public:
    explicit PicturePublisher(networking::MessageSender<networking::AccessPoint>& messageSender,
                              CameraSide cammeraSide);
    void init() override;
    virtual std::string getDefaultName() const override;
private:
    void execute(cv::Mat& image) override;

    networking::MessageSender<networking::AccessPoint>& messageSender_;
    CameraSide cammeraSide_;
};

}  // namespace image_processing
