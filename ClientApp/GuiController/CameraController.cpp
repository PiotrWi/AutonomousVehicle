#include "CameraController.hpp"

#include <RobotClientLib/RobotInterface.hpp>

namespace gui_controller
{

namespace
{

robot_interface::CameraSide translateCameraSide(CameraSide side)
{
    if (CameraSide::Left == side)
    {
        return robot_interface::CameraSide::Left;
    }
    return robot_interface::CameraSide::Right;
}

}  // namespace

void CameraController::subscribeForCameraImages(CameraSide cameraSide, std::function<void(std::shared_ptr<QImage>)> callback)
{
    robot_interface::subscribeForPicture(translateCameraSide(cameraSide), [callback](const robot_interface::IntegerPicture& picture)
    {
        auto qimage = std::make_shared<QImage>(picture.pixels.data(), picture.columns, picture.rows, QImage::Format::Format_BGR888);
        callback(std::move(qimage));
    });
}

} // gui_controller