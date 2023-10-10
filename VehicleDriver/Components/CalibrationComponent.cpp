#include "CalibrationComponent.hpp"

#include <filesystem>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

namespace
{

const int calib_table_rows = 6;
const int calib_table_cols = 9;

void presentBoard(const cv::Mat& mat, const cv::Size& cornersSize, const std::vector<cv::Point2f> corners)
{
    cv::drawChessboardCorners(mat, cornersSize, corners, true);
    cv::imshow("Calibration", mat);
    cv::waitKey(1000);
}

}  // namespace

namespace components
{

std::unique_ptr<Component> createCalibrationComponent(std::string &&calibrationFilesDirectory)
{
    return std::make_unique<CalibrationComponent>(std::move(calibrationFilesDirectory));
}

CalibrationComponent::CalibrationComponent(std::string &&calibrationFilesDirectory)
    : calibrationFilesDirectory_(calibrationFilesDirectory)
{

}

void CalibrationComponent::start()
{
    auto cornersSize = cv::Size (calib_table_cols, calib_table_rows);
    std::vector<std::vector<cv::Point2f>> image_points;
    std::vector<std::vector<cv::Point3f>> object_points;
    cv::Size image_size;

    for (auto const& dir_entry : std::filesystem::directory_iterator{std::filesystem::path(calibrationFilesDirectory_) })
    {
        auto mat = cv::imread(dir_entry.path().string());
        image_size = mat.size();
        std::vector<cv::Point2f> corners;
        auto tableFound = cv::findChessboardCorners(mat, cornersSize, corners);
        if (not tableFound)
        {
            continue;
        }

        image_points.push_back(corners);

        presentBoard(mat, cornersSize, corners);
        if (image_points.size() == 54) break;
    }

    for (auto i = 0u; i < image_points.size(); ++i)
    {
        object_points.push_back(std::vector<cv::Point3f>{});
        auto& opts = object_points.back();
        opts.resize(image_points.size());
        for (auto j=0; j<image_points[0].size(); ++j)
        {
            opts[j] = cv::Point3f ((float)(j/calib_table_cols), (float)(j%calib_table_cols), 0.f);
        }
    }

    cv::Mat intrinsic_matrix, distorion_coeffs;
    double err = cv::calibrateCamera(object_points,
                                     image_points,
                                     image_size,
                                     intrinsic_matrix,
                                     distorion_coeffs,
                                     cv::noArray(),
                                     cv::noArray(),
                                     cv::CALIB_ZERO_TANGENT_DIST | cv::CALIB_FIX_PRINCIPAL_POINT);

    cv::Mat map1, map2;
    cv::initUndistortRectifyMap(intrinsic_matrix, distorion_coeffs,
                                cv::Mat(),intrinsic_matrix, image_size, CV_16SC2, map1, map2);

    std::cout << "Show corrected" << std::endl;

    for (auto const& dir_entry : std::filesystem::directory_iterator{std::filesystem::path(calibrationFilesDirectory_) })
    {
        auto mat1 = cv::imread(dir_entry.path().string());
        cv::Mat mat;
        cv::remap(mat1, mat, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

        cv::imshow("Corrected", mat);
        cv::waitKey(1000);
    }
}

void CalibrationComponent::stop()
{

}

} // components
