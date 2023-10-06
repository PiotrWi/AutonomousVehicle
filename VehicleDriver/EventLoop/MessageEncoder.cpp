#include "MessageEncoder.hpp"

#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include <Tools/Base64.hpp>

using namespace std;

namespace
{

std::string to_string(CameraSide cameraSide)
{
    if (CameraSide::LEFT == cameraSide)
    {
        return "LEFT"s;
    }
    return "RIGHT"s;
}

}  // namespace

class NotImplementedSerialization : public std::runtime_error
{
public:
    explicit NotImplementedSerialization(int type)
        : std::runtime_error("Serialization not implemented for cv type: "s + std::to_string(type)) {}
};

std::string createCurrentRequestedSpeed(int leftWheel, int rightWheel)
{
    return "CurrentRequestedSpeed: "s + std::to_string(leftWheel) + " "s + std::to_string(rightWheel) + "\n";
}



std::string createPublishImage(CameraSide cameraSide, cv::Mat &image)
{
    auto message = "PublishImage: "s
        + to_string(cameraSide) + " "s
        + std::to_string(image.type()) + " "s
        + std::to_string(image.size().width) + "x" + std::to_string(image.size().height);

    if (image.type() == CV_8UC3)
    {
        std::vector<unsigned char> vec;

        std::string out;
        {
            // risky - It makes an assumptions about internal alligment
            vec.resize(image.size().width * image.size().height* 3);
            memcpy(vec.data(), image.ptr(0, 0), vec.size());
            // end of risky

            /* // If there is a problem with risky sollution, bellow one is still valid.
            for (auto it = image.begin<cv::Vec3b>(); it != image.end<cv::Vec3b>(); ++it) {
                vec.push_back((*it)[0]);
                vec.push_back((*it)[1]);
                vec.push_back((*it)[2]);
            }*/
        }
        message += " PAYLOAD: "s + Base64Encode(vec) + "\n";
    }
    else
    {
        throw NotImplementedSerialization(image.type());
    }

    return message;
}
