#include "CorrectImage.hpp"
#include <tuple>

namespace
{

auto readCoefficientFile(const std::string &coefficientFile)
{
    cv::FileStorage fileStorage(coefficientFile, cv::FileStorage::READ);
    cv::Mat camera_matrix, distorion_coeffs;
    fileStorage["camera_matrix"] >> camera_matrix;
    fileStorage["distorion_coeffs"] >> distorion_coeffs;
    cv::Size size;
    fileStorage["image_width"] >> size.width;
    fileStorage["image_height"] >> size.height;
    fileStorage.release();
    return std::make_tuple(camera_matrix, distorion_coeffs, size);
}

}  // namespace

namespace image_processing
{

CorrectImage::CorrectImage(const std::string &coefficientFile)
     : coefficientFile_(coefficientFile)
{
}

void CorrectImage::init()
{
    auto [camera_matrix, distorion_coeffs, image_size]
            = readCoefficientFile(coefficientFile_);
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
    adjustedImage_ = &mat;
    cv::remap(*adjustedImage_,
              *adjustedImage_,
              map1,
              map2,
              cv::INTER_LINEAR,
              cv::BORDER_CONSTANT,
              cv::Scalar());
}

std::any CorrectImage::get(int outputPort)
{
    return std::any(adjustedImage_);
}

} // image_processing