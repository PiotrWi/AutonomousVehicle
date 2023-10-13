#include <opencv2/opencv.hpp>
#include "PrototypeComponent.hpp"

namespace
{

void reactOnMouseClick(int event, int x, int y, int flags, void* param)
{
    std::cout << "React on click" << std::endl;
    if (cv::EVENT_LBUTTONDOWN == event)
    {
        auto corners = reinterpret_cast<std::vector<cv::Point2f>*>(param);
        corners->push_back(cv::Point2f (x, y));
        std::cout << "Add point " << x << ", " << y << std::endl;
    }
}

auto addCornersByHand(cv::Mat image, cv::Size cornersExpectedSize)
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

}  // namespace

namespace components
{

std::unique_ptr<Component> createPrototypeComponent(std::vector<std::unique_ptr<image_processing::Pipeline>> &&pipelines)
{
    return std::make_unique<PrototypeComponent>(std::move(pipelines));
}

PrototypeComponent::PrototypeComponent(std::vector<std::unique_ptr<image_processing::Pipeline>> &&pipelines)
     : pipelines_(std::move(pipelines))
{
}

void PrototypeComponent::stop()
{
}

void PrototypeComponent::start()
{
    auto& pipeline = pipelines_.front();
    pipeline->init();
    pipeline->execute();
    auto image = *std::any_cast<cv::Mat*>(pipeline->getOut());
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

    const int calib_table_rows = 4;
    const int calib_table_cols = 11;
    auto cornersSize = cv::Size (calib_table_cols, calib_table_rows);

    std::vector<cv::Point2f> corners;
    auto found = cv::findCirclesGrid(image, cornersSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
    if (not found)
    {
        std::cerr << "Pattern not found" << std::endl;
        std::cerr << "Found only " << corners.size() << "  corners." << std::endl;
        corners.clear();

        // It is workaround for not finding corners when pattern is on high angle.
        corners = addCornersByHand(image, cornersSize);
        found = true;
    }

    cv::drawChessboardCorners(image, cornersSize, corners, true);
    cv::imshow("PrototypeComponentWithCorners", image);
    cv::waitKey(50);
}

} // components