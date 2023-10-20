#include "MessageEncoder.hpp"

#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include "Tools/Coders/Base64.hpp"
#include <Tools/Checksum.hpp>

using namespace std;

namespace
{

auto translate(CameraSide cameraSide)
{
    if (CameraSide::LEFT == cameraSide)
    {
        return PublishImage_Side_Left;
    }
    return PublishImage_Side_Right;
}

}  // namespace

class NotImplementedSerialization : public std::runtime_error
{
public:
    explicit NotImplementedSerialization(int type)
        : std::runtime_error("Serialization not implemented for cv type: "s + std::to_string(type)) {}
};

CurrentRequestedSpeed createCurrentRequestedSpeed(int leftWheel, int rightWheel)
{
    CurrentRequestedSpeed s;
    s.set_leftwheel(leftWheel);
    s.set_rightwheel(rightWheel);
    return s;
}

PublishImage createPublishImage(CameraSide cameraSide, cv::Mat &image)
{
    PublishImage publishImage;

    publishImage.set_side(translate(cameraSide));
    publishImage.set_format(image.type());
    publishImage.set_width(image.size().width);
    publishImage.set_height(image.size().height);

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
        auto payload = tools::coders::Base64Encode(vec);
        publishImage.set_imagepayload(std::move(payload));
    }
    else
    {
        throw NotImplementedSerialization(image.type());
    }

    return publishImage;
}
