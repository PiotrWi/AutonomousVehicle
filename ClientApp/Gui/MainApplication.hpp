#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include "Gui/QControlPanelView.hpp"
#include "Gui/QCameraView.hpp"
#include "Gui/QLadarVier.hpp"
#include "GuiController/ConnectionController.hpp"

class MainApplication : public QMainWindow
{
    Q_OBJECT;
public:
    MainApplication();
signals:
    void ConnectionStateChanged(bool);
private:
    QWidget* createCentralWidget();
    QWidget* createMenuWidget();
    QStatusBar* createStatusBar();

    gui::QCameraView* leftCameraView_;
    gui::QCameraView* rightCameraView_;
    gui::QLadarView* ladarView_;
    gui::QControlPanelView* controlPanelView_;

    gui_controller::ConnectionController connectionController_;
};
