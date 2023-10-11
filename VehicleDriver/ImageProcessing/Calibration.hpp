#pragma once

#include <string>
#include <tuple>
#include <opencv2/opencv.hpp>

namespace image_processing
{

inline auto readCoeffsFromFile(const std::string& dumpFileName)
{
    cv::Mat camera_matrix, distorion_coeffs;
    cv::Size size;

    cv::FileStorage fileStorage("instrincts_" + dumpFileName + "xml", cv::FileStorage::READ);
    fileStorage["camera_matrix"] >> camera_matrix;
    fileStorage["distorion_coeffs"] >> distorion_coeffs;
    fileStorage["image_width"] >> size.width;
    fileStorage["image_height"] >> size.height;
    fileStorage.release();

    return std::make_tuple(camera_matrix, distorion_coeffs, size);
}

}  // namespace image_processing
