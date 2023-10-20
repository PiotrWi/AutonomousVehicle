#include "PicturePublisher.hpp"

#include <iostream>

#include <EventLoop/MessageEncoder.hpp>
#include <Tools/Checksum.hpp>
namespace image_processing
{

PicturePublisher::PicturePublisher(networking::MessageSender<networking::AccessPoint>& messageSender,
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
    auto out = createPublishImage(cammeraSide_, image);
    messageSender_.send(std::move(out));
}

std::string PicturePublisher::getDefaultName() const
{
    return {"PicturePublisher"};
}

}  // namespace image_processing
