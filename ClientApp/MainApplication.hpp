#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include "Gui/QControlPanelView.hpp"

class QCameraView : public QWidget
{
public:
    explicit QCameraView();
Q_OBJECT;
};

class QLadarView : public QWidget
{
public:
    explicit QLadarView();
Q_OBJECT;
};

class MainApplication : public QMainWindow
{
    Q_OBJECT;
public:
    MainApplication();
private:
    QCameraView leftCameraView_;
    QCameraView rightCameraView_;
    QLadarView ladarView_;
    gui::QControlPanelView controlPanelView_;
};

