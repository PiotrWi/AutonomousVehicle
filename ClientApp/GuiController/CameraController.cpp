#include "CameraController.hpp"

#include <RobotClientLib/RobotInterface.hpp>
#include <utils/DumpImages.hpp>

namespace gui_controller
{

namespace
{

const char* to_string(CameraSide side)
{
    if (CameraSide::Left == side)
    {
        return "Left";
    }
    return "Right";
}

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
    utils::DumpImages dumpImages("/home/pioter/tmp/ClientApp", to_string(cameraSide));
    robot_interface::subscribeForPicture(translateCameraSide(cameraSide), [callback, dumpImages](const robot_interface::IntegerPicture& picture)
    {
        auto qimage = std::make_shared<QImage>(picture.pixels.data(), picture.columns, picture.rows, QImage::Format::Format_BGR888);
        dumpImages.dump(*qimage);

        callback(std::move(qimage));
    });
}

} // gui_controller