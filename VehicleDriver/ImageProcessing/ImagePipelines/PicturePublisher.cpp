#include "PicturePublisher.hpp"

#include <iostream>

#include <EventLoop/MessageEncoder.hpp>

namespace image_processing
{

PicturePublisher::PicturePublisher(networking::MessageSender &messageSender,
                                   CameraSide cammeraSide)
    : messageSender_(messageSender)
    , cammeraSide_(cammeraSide)
{
}

void PicturePublisher::init()
{
}

void PicturePublisher::execute(cv::Mat &image)
{
    std::string out = createPublishImage(cammeraSide_, image);
    messageSender_.send(out);
}

}  // namespace image_processing