#include "QCameraView.hpp"

#include <QLabel>

namespace gui
{

QCameraView::QCameraView()
{
    setMinimumSize(320, 240);
    setStyleSheet("background-color:black;color:white;");

    auto label = new QLabel(this);
    label->setText(QString("Camera view"));

}

}  // namespace gui
