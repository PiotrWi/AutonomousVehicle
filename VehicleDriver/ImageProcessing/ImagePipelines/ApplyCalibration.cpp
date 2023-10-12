#include "ApplyCalibration.hpp"

#include <tuple>

#include <ImageProcessing/Calibration.hpp>

namespace
{

auto to_string(cv::Size size)
{
    return "(" + std::to_string(size.width) + "x" + std::to_string(size.height) + ")";
}

bool validate(cv::Size calibrationSize, cv::Size imageSize)
{
    if (calibrationSize != imageSize)
    {
        std::cerr << "Callibration file was created for different image size. Calibration size is: "
            + to_string(calibrationSize) + ", image size is: " + to_string(imageSize);
        return false;
    }
    return true;
}

}  // namespace

namespace image_processing
{

ApplyCalibration::ApplyCalibration(std::string&& coefficientFile)
     : coefficientFile_(std::move(coefficientFile))
{
}

void ApplyCalibration::init()
{
    auto [camera_matrix, distorion_coeffs, image_size]
            = readCoeffsFromFile(coefficientFile_);
    image_size_ = image_size;
    cv::initUndistortRectifyMap(camera_matrix,
                                distorion_coeffs,
                                cv::Mat(),
                                camera_matrix,
                                image_size,
                                CV_16SC2,
                                map1,
                                map2);
}

void ApplyCalibration::execute(cv::Mat &mat)
{
    static bool calibrationMatch = validate(image_size_, mat.size());
    if (calibrationMatch)
    {
        cv::remap(mat,
                  adjustedImage_,
                  map1,
                  map2,
                  cv::INTER_LINEAR,
                  cv::BORDER_CONSTANT,
                  cv::Scalar());
    }
    else
    {
        adjustedImage_ = mat;
    }
}

std::any ApplyCalibration::get(int outputPort)
{
    return std::any(&adjustedImage_);
}

std::string ApplyCalibration::getDefaultName() const
{
    return {"ApplyCalibration"};
}

} // image_processing