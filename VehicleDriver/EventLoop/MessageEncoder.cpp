#include "MessageEncoder.hpp"

#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include "Tools/Coders/Base64.hpp"
#include "Tools/Coders/HuffmanCoding.hpp"

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

[[maybe_unused]]
auto fillPayloadNoEncoding(PublishImage &publishImage, cv::Mat &image)
{
    std::string payload;
    payload.resize(image.size().width * image.size().height * 3);
    memcpy(payload.data(), image.ptr(0, 0), payload.size());
    publishImage.set_imagepayload(std::move(payload));
}

[[maybe_unused]]
auto fillPayloadWithHuffmanCode(PublishImage &publishImage, cv::Mat &image)
{
    std::vector<unsigned char> imageData;
    imageData.resize(image.size().width * image.size().height * 3);
    memcpy(imageData.data(), image.ptr(0, 0), imageData.size());

    std::string payload;
    auto [payloadLen, codeTable, payloadVec] = tools::coders::encode(imageData);
    payload.resize(payloadLen);
    memcpy(payload.data(), payloadVec.data(), payloadVec.size());

    publishImage.set_imagepayload(std::move(payload));

    auto huffmanCode = new PublishImage_HuffmanCodingData();
    huffmanCode->set_len(payloadLen);
    for(auto code: codeTable)
    {
        huffmanCode->add_codevalue(code.mask);
        huffmanCode->add_colelen(code.len);
    }
    publishImage.set_allocated_hufman(huffmanCode);
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
        // fillPayloadNoEncoding(publishImage, image);
        fillPayloadWithHuffmanCode(publishImage, image);
    }
    else
    {
        throw NotImplementedSerialization(image.type());
    }

    return publishImage;
}
