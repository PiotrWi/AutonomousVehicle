#include "CalibrationComponent.hpp"

#include <filesystem>
#include <iostream>
#include <tuple>

#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

#include <ImageProcessing/Calibration.hpp>

namespace
{

const int calib_table_rows = 6;
const int calib_table_cols = 9;

void presentBoard(const cv::Mat& mat, const cv::Size& cornersSize, const std::vector<cv::Point2f> corners)
{
    cv::drawChessboardCorners(mat, cornersSize, corners, true);
    cv::imshow("Calibration", mat);
    cv::waitKey(50);
}

auto calculateImagePoints(const std::string& calibrationFilesDirectory_)
{
    auto cornersSize = cv::Size (calib_table_cols, calib_table_rows);
    std::vector<std::vector<cv::Point2f>> image_points;
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
        if (image_points.size() == 30) break;
    }
    return std::make_tuple(image_points, image_size);
}

auto calculateObjectPoints(int objects, int cornersSize)
{
    std::vector<std::vector<cv::Point3f>> object_points;
    for (auto i = 0u; i < objects; ++i)
    {
        object_points.push_back(std::vector<cv::Point3f>{});
        auto& opts = object_points.back();
        opts.resize(cornersSize);
        for (auto j=0; j<cornersSize; ++j)
        {
            opts[j] = cv::Point3f ((float)(j/calib_table_cols)*0.24, (float)(j%calib_table_cols)*0.24, 0.f);
        }
    }
    return object_points;
}

auto calibrate(const std::vector<std::vector<cv::Point3f>>& object_points, const std::vector<std::vector<cv::Point2f>>& image_points, cv::Size image_size)
{
    cv::Mat intrinsic_matrix, distorion_coeffs;
    double err = cv::calibrateCamera(object_points,
                                     image_points,
                                     image_size,
                                     intrinsic_matrix,
                                     distorion_coeffs,
                                     cv::noArray(),
                                     cv::noArray(),
                                     cv::CALIB_ZERO_TANGENT_DIST | cv::CALIB_FIX_PRINCIPAL_POINT);
    std::cout << "Err: " << err << std::endl;
    return std::make_tuple(intrinsic_matrix, distorion_coeffs);
}

auto dumpCoeffsToFile(const std::string& dumpFileName, cv::Size image_size, cv::Mat intrinsic_matrix, cv::Mat distorion_coeffs)
{
    cv::FileStorage fileStorage("instrincts_" + dumpFileName + ".xml", cv::FileStorage::WRITE);
    fileStorage << "image_width" << image_size.width
        << "image_height" << image_size.height
        << "camera_matrix" << intrinsic_matrix
        << "distorion_coeffs" << distorion_coeffs;
    fileStorage.release();
}

auto previewResults(std::string calibrationFilesDirectory, std::string dumpFileName)
{
    auto [camera_matrix, distorion_coeffs, size] = image_processing::readCoeffsFromFile("instrincts_" + dumpFileName + ".xml");
    std::cout << "intrinsic_matrix: " << camera_matrix << std::endl << std::endl;
    std::cout << "distorion_coeffs: " << distorion_coeffs << std::endl << std::endl;
    cv::Mat map1, map2;
    cv::initUndistortRectifyMap(camera_matrix, distorion_coeffs,
                                cv::Mat(),camera_matrix, size, CV_16SC2, map1, map2);

    for (auto const& dir_entry : std::filesystem::directory_iterator{std::filesystem::path(calibrationFilesDirectory) })
    {
        auto mat1 = cv::imread(dir_entry.path().string());
        cv::Mat mat;
        cv::remap(mat1, mat, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

        cv::imshow("Corrected", mat);
        cv::waitKey(1000);
    }
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
    if (not exists(std::filesystem::path(calibrationFilesDirectory_)))
    {
        std::cerr << "Directory given for calibration does not exist";
    }

    auto dumpFileName = calibrationFilesDirectory_.substr(1 + calibrationFilesDirectory_.find_last_of("/"), std::string::npos);
    auto [image_points, image_size] = calculateImagePoints(calibrationFilesDirectory_);
    auto object_points = calculateObjectPoints(image_points.size(), image_points[0].size());
    auto [intrinsic_matrix, distorion_coeffs] = calibrate(object_points, image_points, image_size);

    std::cout << "intrinsic_matrix: " << intrinsic_matrix << std::endl << std::endl;
    std::cout << "distorion_coeffs: " << distorion_coeffs << std::endl << std::endl;

    dumpCoeffsToFile(dumpFileName, image_size, intrinsic_matrix, distorion_coeffs);



    cv::Mat map1, map2;
    cv::initUndistortRectifyMap(intrinsic_matrix, distorion_coeffs,
                                cv::Mat(),intrinsic_matrix, image_size, CV_16SC2, map1, map2);

    /*for (auto const& dir_entry : std::filesystem::directory_iterator{std::filesystem::path(calibrationFilesDirectory_) })
    {
        auto mat1 = cv::imread(dir_entry.path().string());
        cv::Mat mat;
        cv::remap(mat1, mat, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

        cv::imshow("Corrected", mat);
        cv::waitKey(1000);
    }*/
    previewResults(calibrationFilesDirectory_, dumpFileName);
}

void CalibrationComponent::stop()
{

}

} // components
