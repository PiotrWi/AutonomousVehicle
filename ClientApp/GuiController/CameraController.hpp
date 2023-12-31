#pragma once

#include <functional>

#include <QImage>

#include <Tools/SingletonAddOn.hpp>

namespace gui_controller
{

enum class CameraSide
{
    Left,
    Right,
};

class CameraController : public SingletonAddOn<CameraController>
{
public:
    static void subscribeForCameraImages(CameraSide cameraSide,
                                         const std::function<void(std::shared_ptr<QImage>)>& callback);
};

} // gui_controller
