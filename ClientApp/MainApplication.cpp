#include "MainApplication.hpp"

#include <iostream>

#include <QKeyEvent>
#include <QLabel>

MainApplication::MainApplication()
    : leftCameraView_()
    , rightCameraView_()
    , ladarView_()
    , controlPanelView_()
{
    setMinimumSize(640, 480);

    auto layout = new QGridLayout();
    layout->addWidget(&leftCameraView_, 0, 0);
    layout->addWidget(&rightCameraView_, 0, 1);
    layout->addWidget(&ladarView_, 1, 0);
    layout->addWidget(&controlPanelView_, 1, 1);

    auto cWidget = new QWidget();
    cWidget->setLayout(layout);

    setCentralWidget(cWidget);
}

QCameraView::QCameraView()
{
    setMinimumSize(320, 240);
    setStyleSheet("background-color:black;color:white;");

    auto label = new QLabel(this);
    label->setText(QString("Camera view"));

}

QLadarView::QLadarView()
{
    auto label = new QLabel(this);
    label->setText(QString("LadarView"));
    setMinimumSize(320, 240);
    setStyleSheet("background-color:blue;color:white;");
}


