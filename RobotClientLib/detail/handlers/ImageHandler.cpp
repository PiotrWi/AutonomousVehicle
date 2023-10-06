#include "ImageHandler.hpp"

#include <iostream>
#include <sstream>
#include "Tools/StringAlgorithms.hpp"
#include "Tools/Base64.hpp"

using namespace std;

std::istream& operator>>(std::istream& stream, robot_interface::CameraSide& direction)
{
     std::string out;
     stream >> out;
     if (out == "LEFT"s)
     {
         direction = robot_interface::CameraSide::Left;
     }
     if (out == "RIGHT"s)
     {
         direction = robot_interface::CameraSide::Right;
     }
     return stream;
}

namespace
{

void fullfillRowsAndHeights(std::istream& stream, int& rows, int& columns)
{
    std::string out;
    stream >> out;
    auto sizeVec = splitAndTrim(out, 'x');
    rows = std::stoi(sizeVec[1]);
    columns = std::stoi(sizeVec[0]);
}

}  // namespace

void ImageHandler::handle(const std::string& message)
{
    std::stringstream ss(message.substr(getPrefix().size()));
    robot_interface::CameraSide side;
    robot_interface::IntegerPicture out;

    ss >> side;
    ss >> out.format;
    fullfillRowsAndHeights(ss, out.rows, out.columns);

    auto payloadPosition  = message.find("PAYLOAD:");
    if (payloadPosition == std::string::npos)
    {
        return;
    }

    std::string_view sw (message.begin() + payloadPosition + 9, message.end());
    out.pixels = Base64Decode(message.substr(payloadPosition + 9));

    function<void(robot_interface::IntegerPicture)> notifier;
    {
        std::lock_guard<std::mutex> lock(contentMutex_);
        notifier = content_[side].first;
        content_[side].second = out;
    }

    notifier(out);
}

std::string ImageHandler::getPrefix()
{
    return "PublishImage:"s;
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
    content_[cameraSide].first = callback;
}

