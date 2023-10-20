#include "ImageHandler.hpp"

#include <iostream>
#include <sstream>
#include "Tools/StringAlgorithms.hpp"
#include "Tools/Coders/Base64.hpp"

using namespace std;


namespace
{

robot_interface::CameraSide translate(decltype(declval<PublishImage>().side()) side)
{
    if (side == PublishImage_Side_Left)
    {
        return robot_interface::CameraSide::Left;
    }
    return robot_interface::CameraSide::Right;
}

}  // namespace

void ImageHandler::handle(const PublishImage& message)
{
    robot_interface::CameraSide side = translate(message.side());
    robot_interface::IntegerPicture out;
    out.format = message.format();
    out.rows = message.height();
    out.columns = message.width();

    out.pixels = tools::coders::Base64Decode(message.imagepayload().data() );

    function<void(robot_interface::IntegerPicture)> notifier;
    {
        std::lock_guard<std::mutex> lock(contentMutex_);
        notifier = content_[side].first;
        content_[side].second = out;
    }

    notifier(out);
}

void ImageHandler::clear()
{
}

robot_interface::IntegerPicture ImageHandler::getImage(robot_interface::CameraSide cameraSide)
{
    std::lock_guard<std::mutex> m(contentMutex_);
    return content_[cameraSide].second;
}

void ImageHandler::subscribeForPicture(robot_interface::CameraSide cameraSide,
                                       std::function<void(robot_interface::IntegerPicture)> callback)
{
    std::lock_guard<std::mutex> m(contentMutex_);
    content_[cameraSide].first = std::move(callback);
}


