#pragma once

#include <QWidget>
#include <QLabel>
#include <GuiController/CameraController.hpp>

namespace gui
{

class QCameraView : public QWidget
{
Q_OBJECT;
public:
    explicit QCameraView(gui_controller::CameraSide cameraSide);
signals:
    void imageChanged(std::shared_ptr<QImage>);
public:
    void resizeEvent(QResizeEvent *event) override;
    void displayImage(std::shared_ptr<QImage>);
private:
    gui_controller::CameraController cameraController_;
    QLabel* image_;
};

}  // namespace gui
