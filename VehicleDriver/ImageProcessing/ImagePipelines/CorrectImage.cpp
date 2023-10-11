#include "CorrectImage.hpp"

#include <tuple>

#include <ImageProcessing/Calibration.hpp>


namespace
{

bool validate(cv::Size calibrationSize, cv::Size imageSize)
{
    if (calibrationSize != imageSize)
    {
        throw std::logic_error("Callibration file was created for different image size.");
    }
    return true;
}

}  // namespace

namespace image_processing
{

CorrectImage::CorrectImage(std::string&& coefficientFile)
     : coefficientFile_(std::move(coefficientFile))
{
}

void CorrectImage::init()
{
    auto [camera_matrix, distorion_coeffs, image_size]
            = readCoeffsFromFile(coefficientFile_);
    cv::initUndistortRectifyMap(camera_matrix,
                                distorion_coeffs,
                                cv::Mat(),
                                camera_matrix,
                                image_size,
                                CV_16SC2,
                                map1,
                                map2);
}

void CorrectImage::execute(cv::Mat &mat)
{
    static bool validateOnce = validate(image_size_, mat.size());

    cv::remap(mat,
              adjustedImage_,
              map1,
              map2,
              cv::INTER_LINEAR,
              cv::BORDER_CONSTANT,
              cv::Scalar());
}

std::any CorrectImage::get(int outputPort)
{
    return std::any(&adjustedImage_);
}

} // image_processing