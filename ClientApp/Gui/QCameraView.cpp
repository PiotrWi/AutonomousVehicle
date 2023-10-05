#include "QCameraView.hpp"

#include <QLabel>
#include <QSizePolicy>
#include <QResizeEvent>

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
    auto labelSize = image_->size();
    auto scaled = image->scaled(labelSize.width(), labelSize.height(), Qt::AspectRatioMode::KeepAspectRatio);

    QPixmap pixMap;
    pixMap.convertFromImage(scaled);
    image_->setPixmap(pixMap);
}

void QCameraView::resizeEvent(QResizeEvent *event)
{
    image_->resize(event->size());
    QWidget::resizeEvent(event);
}

}  // namespace gui
