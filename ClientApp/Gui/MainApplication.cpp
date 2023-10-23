#include "MainApplication.hpp"

#include <iostream>

#include <QKeyEvent>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

#include <GuiController/SetEnableManager.hpp>
#include "ConnectionDialog.hpp"

namespace gui
{

namespace
{

void addFileMenu(QMenuBar* menuBar);
void addConnectAction(QMenu* menu);
void addDisconnectAction(QMenu* menu);

void addFileMenu(QMenuBar* menuBar)
{
    auto fileMenu = new QMenu("File");

    addConnectAction(fileMenu);
    addDisconnectAction(fileMenu);

    menuBar->addMenu(fileMenu);
}

void addConnectAction(QMenu* menu)
{
    auto connectAction = new QAction("Connect");
    menu->connect(connectAction, &QAction::triggered,
                  [mainWindow = menu->parentWidget()](auto&&){
                      std::cout << "Connect clicked" << std::endl;
                      auto connectionDialog = new ConnectionDialog(mainWindow);
                      auto retVal = connectionDialog->exec();
                      auto ipParameters = connectionDialog->getValue();

                      if (retVal && ipParameters)
                      {
                          gui_controller::ConnectionController::getInstance().connect(ipParameters->ip_, ipParameters->port_);
                      }
                  } );
    connectAction->setEnabled(true);
    gui_controller::SetEnableManager::getInstance().registerItem(connectAction, gui_controller::EnabledWhenConnectionDown{});

    menu->addAction(connectAction);
}

void addDisconnectAction(QMenu* menu)
{
    auto connectAction = new QAction("Disconnect");
    menu->connect(connectAction, &QAction::triggered,
                  [](auto&&){
                      std::cout << "Disconnect clicked" << std::endl;
                      gui_controller::ConnectionController::getInstance().disconnect();
                  } );
    connectAction->setEnabled(false);
    gui_controller::SetEnableManager::getInstance().registerItem(connectAction, gui_controller::EnabledWhenConnectionUp{});

    menu->addAction(connectAction);
}

}  // namespace

MainApplication::MainApplication()
    : leftCameraView_(new gui::QCameraView(gui_controller::CameraSide::Left))
    , rightCameraView_(new gui::QCameraView(gui_controller::CameraSide::Right))
    , ladarView_(new gui::QLadarView)
    , controlPanelView_(new gui::QControlPanelView)
{
    setMinimumSize(640, 480);

    auto cWidget = createCentralWidget();
    setCentralWidget(cWidget);

    auto menu = createMenuWidget();
    setMenuWidget(menu);

    auto statusBar = createStatusBar();
    statusBar->setParent(this);
    statusBar->showMessage("Not connected");
    setStatusBar(statusBar);

    controlPanelView_->setEnabled(false);
    gui_controller::SetEnableManager::getInstance().registerItem(controlPanelView_, gui_controller::EnabledWhenConnectionUp{});
    gui_controller::ConnectionController::getInstance().registerConnectionChanged([&](bool isConnectionActive){
        emit ConnectionStateChanged(isConnectionActive);
    });
    connect(this, &MainApplication::ConnectionStateChanged,
            [&](bool isConnectionActive){
                    if (isConnectionActive)
                    {
                        gui_controller::SetEnableManager::getInstance().reactOnConnected();
                        this->statusBar()->showMessage("connected");
                    }
                    else
                    {
                        gui_controller::SetEnableManager::getInstance().reactOnDisconnected();
                        this->statusBar()->showMessage("Not connected");
                    }
    });
}

QWidget* MainApplication::createCentralWidget()
{
    auto layout = new QGridLayout();
    layout->addWidget(leftCameraView_, 0, 0);
    layout->addWidget(rightCameraView_, 0, 1);
    layout->addWidget(ladarView_, 1, 0);
    layout->addWidget(controlPanelView_, 1, 1);

    auto cWidget = new QWidget();
    cWidget->setLayout(layout);

    return cWidget;
}



QWidget* MainApplication::createMenuWidget()
{
    auto menuBar = new QMenuBar(this);

    addFileMenu(menuBar);

    return menuBar;
}

QStatusBar* MainApplication::createStatusBar()
{
    return new QStatusBar();
}

}  // namespace gui
