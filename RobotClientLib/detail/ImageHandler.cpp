#include "ImageHandler.hpp"

#include <iostream>
#include <sstream>
#include <Tools/StringAlgorithms.hpp>
#include <Tools/Base64.hpp>

using namespace std;

/*
 *     auto message = "PublishImage: "s
        + "LEFT "s
        + std::to_string(image.type()) + " "s
        + std::to_string(image.size().width) + "x" + std::to_string(image.size().height);

    if (image.type() == CV_8UC3)
    {
        static std::vector<unsigned char> vec;
        static std::string out;
        vec.clear();
        {
            for (auto it = image.begin<cv::Vec3b>(); it != image.end<cv::Vec3b>(); ++it) {
                vec.push_back((*it)[0]);
                vec.push_back((*it)[1]);
                vec.push_back((*it)[2]);
            }
        }
        message += " PAYLOAD: "s + encodeBase64(vec) + "\n";
    }
    else
    {
        throw NotImplementedSerialization(image.type());
    }
 */
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

    std::lock_guard<std::mutex> lock(contentMutex_);
    std::swap(content_[side].second, out);
    content_[side].first(content_[side].second);
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


