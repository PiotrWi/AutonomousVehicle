#include "Calibration.hpp"
#include <ImageProcessing/ImageOperations/ImageOperators.hpp>

namespace image_processing
{

namespace
{

void reactOnMouseClick(int event, int x, int y, int flags, void* param)
{
    if (cv::EVENT_LBUTTONDOWN == event)
    {
        auto corners = reinterpret_cast<std::vector<cv::Point2f>*>(param);
        corners->push_back(cv::Point2f (x, y));
        std::cout << "Add point " << x << ", " << y << std::endl;
    }
}

}  // namspeace

std::tuple<TCameraMatrix, TDistortionMatrix, TImageSize>  readCoeffsFromFile(const std::string& dumpFileLocation)
{
    cv::Mat camera_matrix, distorion_coeffs;
    cv::Size size;

    cv::FileStorage fileStorage(dumpFileLocation, cv::FileStorage::READ);
    fileStorage["camera_matrix"] >> camera_matrix;
    fileStorage["distorion_coeffs"] >> distorion_coeffs;
    fileStorage["image_width"] >> size.width;
    fileStorage["image_height"] >> size.height;
    fileStorage.release();

    return std::make_tuple(camera_matrix, distorion_coeffs, size);
}

TImageCalibrationPoints addCornersByHand(cv::Mat image, cv::Size cornersExpectedSize)
{
    std::vector<cv::Point2f> corners;

    cv::imshow("SetPointsByHand", image);
    cv::setMouseCallback("SetPointsByHand", reactOnMouseClick, &corners);

    while (corners.size() != cornersExpectedSize.height*cornersExpectedSize.width)
    {
        cv::waitKey(15);
    }

    return corners;
}


std::tuple<TFound, TImageCalibrationPoints> findCornersByKMeans(cv::Mat mat, cv::Size2i size)
{
    auto image = mat.clone();
    std::vector<cv::Point2f> corners;
    auto thresholded = mat.clone() | ToBinary{} | BinaryAdaptiveTreshold(91, 50);
    cv::imshow("AfterTreshold", thresholded);

    std::vector<cv::Point2f> blackPixels;
    for (auto it = thresholded.begin<unsigned char>(); it != thresholded.end<unsigned char>(); ++it)
    {
        if (*it == 0)
        {
            blackPixels.push_back(it.pos());
        }
    }

    cv::Mat labels, centers;
    cv::kmeans(blackPixels,
               size.height*size.width,
               labels,
               cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 1500, 1.0),
               50,
               cv::KMEANS_PP_CENTERS,
               centers);

    for (auto i = 0u; i < size.height*size.width; ++i)
    {
        corners.push_back(centers.at<cv::Point2f>(i));
    }
    cv::drawChessboardCorners(image, size, corners, true);
    cv::imshow("findCornersByKMeans", image);
    cv::waitKey(50);
    return {true, corners};
}

std::tuple<TFound, TImageCalibrationPoints> findChessBoardCornersByOpenCv(cv::Mat image, cv::Size2i cornersSize)
{
    std::vector<cv::Point2f> corners;
    auto found = cv::findChessboardCorners(image, cornersSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
    return {found, corners};
}

void printCorners(std::string windowName, cv::Mat image, cv::Size size, const TImageCalibrationPoints &points)
{
    cv::drawChessboardCorners(image, size, points, true);
    cv::imshow(windowName, image);
    cv::waitKey(50);
}

std::tuple<bool, std::vector<cv::Point2f>> findCornerOnTransformedImage(cv::Mat image, cv::Size cornersSize)
{
    std::vector<cv::Point2f> corners;
    cv::Point2f sourcePoints[4] = {
            {190, 306},  // left upper
            {389, 306},  // right upper
            {491, 415},  // right down
            {79, 415},   // left down

    };
    cv::Point2f destinationPoints[4] = {
            {120, 306},
            {390, 306},
            {491, 415},
            {79, 415},
    };
    auto perspectiveMatrix = cv::getPerspectiveTransform(sourcePoints, destinationPoints);
    cv::Mat transformedImage;
    cv::warpPerspective(image, transformedImage, perspectiveMatrix, image.size(), cv::INTER_LINEAR);

    auto found = cv::findChessboardCorners(transformedImage, cornersSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
    cv::imshow("transformedImage", transformedImage);
    cv::waitKey(50);

    return std::make_tuple(found, corners);
}



}  // namespace image_processing
