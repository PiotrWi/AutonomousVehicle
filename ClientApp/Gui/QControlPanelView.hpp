#pragma once

#include <QWidget>
#include "../GuiController/KeyPressController.hpp"

class QKeyEvent;

class QLabel;
class QLineEdit;

namespace gui
{

class QControlPanelView : public QWidget
{
    Q_OBJECT;
signals:
    void changeEvent(QEvent *) override;
    void requestedSpeedChanged(gui_controller::Speeds);
public:
    explicit QControlPanelView();

    void start();
    void stop();

    void keyPressEvent(QKeyEvent *event) override;
private:
    void createSpeedsWidgets();
    void connectSpeedWidgetsToSpeedChanges();
    void fullfillSpeeds();

    gui_controller::KeyPressController& keyPressController_;
    std::optional<bool> isStarted_;

    QLabel *requestedLeftWheelSpeedLabel_;
    QLineEdit *requestedLeftWheelSpeedOut_;
    QLabel *requestedRightWheelSpeedLabel_;
    QLineEdit *requestedRightWheelSpeedOut_;
};

}  // namespace gui
