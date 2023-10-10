#include "MessageEncoder.hpp"

#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include <Tools/Base64.hpp>
#include <Tools/Checksum.hpp>

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

        if (image.isContinuous())
        {
            vec.resize(image.size().width * image.size().height* 3);
            memcpy(vec.data(), image.ptr(0, 0), vec.size());
        }
        else
        {
            std::cout << "Not continous matrix" << std::endl;
            for (auto it = image.begin<cv::Vec3b>(); it != image.end<cv::Vec3b>(); ++it)
            {
                vec.push_back((*it)[0]);
                vec.push_back((*it)[1]);
                vec.push_back((*it)[2]);
            }
        }
        auto payload = Base64Encode(vec);
        auto crc = calculateChecksum(payload.begin(), payload.end());
        message += " CRC: "s + std::to_string(crc);
        message += " PAYLOAD: "s + Base64Encode(vec) + "\n";

        VERIFY_CHECKSUM(message);
    }
    else
    {
        throw NotImplementedSerialization(image.type());
    }

    return message;
}
