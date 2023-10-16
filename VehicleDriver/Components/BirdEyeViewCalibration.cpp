#include <opencv2/opencv.hpp>
#include "BirdEyeViewCalibration.hpp"

#include <ImageProcessing/Calibration.hpp>

namespace
{

cv::Mat extractSingleFrameFromPipeline(image_processing::Pipeline& pipeline)
{
    pipeline.init();
    pipeline.execute();
    return *std::any_cast<cv::Mat*>(pipeline.getOut());
}

constexpr int calib_table_rows = 3;
constexpr int calib_table_cols = 3;

}  // namespace

namespace components
{

std::unique_ptr<Component> createBirdEyeViewCalibration(std::vector<std::unique_ptr<image_processing::Pipeline>> &&pipelines)
{
    return std::make_unique<BirdEyeViewCalibration>(std::move(pipelines));
}

BirdEyeViewCalibration::BirdEyeViewCalibration(std::vector<std::unique_ptr<image_processing::Pipeline>> &&pipelines)
        : pipelines_(std::move(pipelines))
{
}

void BirdEyeViewCalibration::stop()
{
}

void BirdEyeViewCalibration::start()
{
    auto image = extractSingleFrameFromPipeline(*pipelines_.front());
    auto cornersSize = cv::Size (calib_table_cols, calib_table_rows);

    auto [found, corners] = image_processing::findChessBoardCornersByOpenCv(image, cornersSize);
    if (not found)
    {
        std::cerr << "Pattern not found" << std::endl;
        std::cerr << "Found only " << corners.size() << "  corners." << std::endl;
        corners.clear();
        corners = image_processing::addCornersByHand(image, cornersSize);
    }

    image_processing::printCorners("PrototypeComponentWithCorners", image, cornersSize, corners);

    cv::Point2f imagePoints[4] {
            corners[0],
            corners[cornersSize.width -1],
            corners.back(),
            corners[(cornersSize.height-1)*cornersSize.width],
    };
    cv::Point2f objectPoints[4]{
            {218, 169},
            {421, 169},
            {421, 311},
            {218, 311},
    };

    auto H = cv::getPerspectiveTransform(imagePoints, objectPoints);

    cv::Mat birdEye;
    cv::warpPerspective(image, birdEye, H, image.size(),  cv::INTER_LINEAR,
                        cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::imshow("BirdEye", birdEye);
    cv::waitKey();
}



} // components