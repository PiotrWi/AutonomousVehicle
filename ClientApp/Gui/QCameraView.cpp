#include "QCameraView.hpp"

#include <QLabel>

namespace gui
{

QCameraView::QCameraView(gui_controller::CameraSide cameraSide)
    : cameraSide_(cameraSide)
    , cameraController_(gui_controller::CameraController::getInstance())
{
    setMinimumSize(320, 240);
    setStyleSheet("background-color:black;color:white;");

    image_ = new QLabel(this);
    image_->setMinimumSize(320, 240);

    cameraController_.subscribeForCameraImages(cameraSide, [this](std::shared_ptr<QImage> image){
        emit displayImage(std::move(image));
    });
    connect(this, &QCameraView::imageChanged, this, &QCameraView::displayImage);
}

void QCameraView::displayImage(std::shared_ptr<QImage> image)
{
    QPixmap pixMap;
    pixMap.convertFromImage(*image);
    image_->setPixmap(pixMap);
}

}  // namespace gui
